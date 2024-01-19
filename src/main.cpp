#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
//I know. Maybe I could have saved some libraries if I actually know how to solve these problems myself.
//However, this would be a good prototype that I could optimze if this didn't meet specification.
//As this is an assignment with no optimization in the rubric, what's here is within spec. I'm keeping it.


class Run{
    public:
        std::ifstream inFile;
        std::string buf;
        std::vector<std::string> accounts;
        std::vector<long> moneyInAccount; //in cents
        Run(std::string fileLocation){
            
            //Major steps could have been methods so that the stack memory is unwound when exiting each step 
            //instead of leaving useless memory until the constructor is finished.

            // I: Open file.
            inFile.open(fileLocation);
            if (!inFile.is_open()) {
                std::cout << "Unable to open file";
                exit(1); // terminate with error
            }
            std::cout << "Please wait for file to proccess..." << std::endl;

            // II: Deserialize the file by moving them to vectors.
            int currentAccount = 0;
            long currentTransactionAmount = 0;
            const long min_int = std::numeric_limits<long>::min();
            const long max_int = std::numeric_limits<long>::max();
            
            while (inFile >> buf) {

                //Step 1: search for matching account. If none, create a new one.
                currentAccount = getIndex(accounts, buf);
                if(currentAccount == -1){
                    accounts.resize(accounts.size() + 1);
                    moneyInAccount.resize(moneyInAccount.size() + 1);
                    accounts.back() = buf;
                    currentAccount = getIndex(accounts, buf);
                }
                //Step 2: Memorize the value of transaction.
                inFile >> buf;
                currentTransactionAmount = static_cast<long>(std::stof(buf) * 100);


                //Step 3: Subtract or add to their account.
                inFile >> buf;
                long previousValue = 0;

                previousValue = moneyInAccount[currentAccount];
                if(buf == "deposit"){
                    moneyInAccount[currentAccount] += currentTransactionAmount;
                    if(moneyInAccount[currentAccount] < previousValue){
                        std::cout << "Error: Overflow on account " << accounts[currentAccount] << std::endl;
                    }
                }
                else if(buf == "withdrawal"){
                    moneyInAccount[currentAccount] -= currentTransactionAmount;
                    if(moneyInAccount[currentAccount] > previousValue){
                        std::cout << "Error: Underflow on account " << accounts[currentAccount] << std::endl;
                    }
                }
            }
            
            //This major step could have been run in main() so that I can close the file before it writes the accounts to the shell.

            //III: Display the accounts to console
            std::string currentStanding;
            std::string accountLine;

            std::cout << std::endl;
            for(int i = 0; i < accounts.size(); i++){
                if(moneyInAccount[i] < 0){
                    currentStanding = "Withdrawn";
                }else {
                    currentStanding = "In Good Standing";
                }
                accountLine = accounts[i] + " $" + std::to_string(moneyInAccount[i] / 100) + "." + apendZero(std::abs(moneyInAccount[i] % 100)) + " " + currentStanding;
                std::cout << accountLine << std::endl;
            }
        }
        ~Run(){
            inFile.close();
        }

        int getIndex(std::vector<std::string> v, std::string K) 
        { 
            auto it = find(v.begin(), v.end(), K); 
  
            // If element was found 
            if (it != v.end())  
            { 
            
                // calculating the index 
                // of K 
                int index = it - v.begin(); 
                return index;
            } 
            else { 
                // If the element is not 
                // present in the vector 
                return -1;
            } 
        } 

        std::string apendZero(long cents){
            std::stringstream ss;
            ss.clear();
            ss << std::setfill('0') << std::setw(2) << std::to_string(cents);
            return ss.str();
        }
};

int main()
{
    //Honestly, I would love to add a record system where it records my proccess times and so I can compete for better times.
    //But I'm getting tired.
    
    time_t start, end; 
    time(&start); 
    // unsync the I/O of C and C++. 
    std::ios_base::sync_with_stdio(false); 
    
    std::filesystem::path cwd = std::filesystem::current_path();
    Run run(cwd.string() + "\\output\\output.txt");
    
    time(&end); 
    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    std::cout << std::endl << "Procces completed in " << std::fixed << time_taken << std::setprecision(5); 
    std::cout << " seconds." << std::endl; 
    
    return 0;
}