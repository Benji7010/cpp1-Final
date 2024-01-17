import random
import string
num_lines = 100
account_nums = [''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10)) for _ in range(10)]
# Function to generate a random line in the specified format
def generate_random_transaction():
    random_string = random.choice(account_nums)
    amount = round(random.uniform(1.00, 999.99), 2)
    transaction_type = random.choice(["deposit", "withdrawal"])
    return f"{random_string} {amount:.2f} {transaction_type}\n"
# Open the file in write mode
with open('./output/output.txt', 'w') as file:
    # Generate and write random lines to the file
    for _ in range(num_lines):
        line = generate_random_transaction()
        file.write(line)