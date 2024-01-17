#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class Run{
    public:
        std::ifstream inFile;
        std::string buf;
        std::vector<std::string> accounts;
        std::vector<float> moneyInAccount;
        Run(std::string fileLocation){
            int currentAccount = 0;
            float currentTransactionAmount = 0;
            
            // I: Open file.
            inFile.open(fileLocation);
            if (!inFile.is_open()) {
                std::cout << "Unable to open file";
                exit(1); // terminate with error
            }

            // II: Deserialize the file by moving them to vectors.
            while (inFile >> buf) {
                std::cout << buf << std::endl;

                //Step 1: search for matching account. If none, create a new one.
                currentAccount = getIndex(accounts, buf);
                if(currentAccount == -1){
                    accounts.resize(accounts.size() + 1);
                    moneyInAccount.resize(moneyInAccount.size() + 1);
                    currentAccount = getIndex(accounts, buf);
                }
                std::cout << currentAccount << std::endl;
                //Step 2: Write the value of transaction.
                inFile >> buf;
                std::cout << buf << std::endl;
                currentTransactionAmount = std::stof(buf);

                //Step 3: Subtract or add to their account.
                inFile >> buf;
                std::cout << buf << std::endl;
                if(buf == "deposit"){
                    moneyInAccount[currentAccount] += currentTransactionAmount;
                }
                else if(buf == "withdrawal"){
                    moneyInAccount[currentAccount] -= currentTransactionAmount;
                }
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
};

int main()
{
    Run run("C:\\Users\\benji\\Documents\\GitHub\\cpp1-Final\\output\\output.txt");
}