#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

/* ---------------- Transaction Class ---------------- */

class Transaction 
{
public:
    string type;
    double amount;

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }
};

/* ---------------- Account Class ---------------- */

class Account 
{
public:
    int accountNumber;
    double balance;
    vector<Transaction> history;

    Account(int accNo) {
        accountNumber = accNo;
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            history.push_back(Transaction("Withdraw", amount));
            cout << "Withdrawal successful!\n";
        }
    }

    void showTransactions() {
        cout << "\nTransaction History\n";
        cout << "-----------------------------\n";
        for (auto &t : history) {
            cout << left << setw(15) << t.type
                 << setw(10) << t.amount << endl;
        }
    }
};

/* ---------------- Customer Class ---------------- */

class Customer {
public:
    string name;
    int id;
    Account account;

    Customer(string n, int i, int accNo) : account(accNo) {
        name = n;
        id = i;
    }

    void displayInfo() {
        cout << "\nCustomer Name: " << name << endl;
        cout << "Customer ID: " << id << endl;
        cout << "Account Number: " << account.accountNumber << endl;
        cout << "Current Balance: " << account.balance << endl;
    }
};

/* ---------------- Transfer Function ---------------- */

void transferMoney(Account &from, Account &to, double amount) {

    if (amount > from.balance) {
        cout << "Transfer failed! Not enough balance.\n";
        return;
    }

    from.balance -= amount;
    to.balance += amount;

    from.history.push_back(Transaction("Transfer Out", amount));
    to.history.push_back(Transaction("Transfer In", amount));

    cout << "Transfer successful!\n";
}

/* ---------------- Main Program ---------------- */

int main() 
{

    vector<Customer> customers;
    int choice;

    do {
        cout << "\n===== BANKING SYSTEM =====\n";
        cout << "1. Create Customer Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. View Account Details\n";
        cout << "6. View Transaction History\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int id, accNo;

            cout << "Enter customer name: ";
            cin >> name;

            cout << "Enter customer ID: ";
            cin >> id;

            cout << "Enter account number: ";
            cin >> accNo;

            customers.push_back(Customer(name, id, accNo));
            cout << "Customer account created successfully!\n";
        }

        else if (choice == 2) {
            int accNo;
            double amount;

            cout << "Enter account number: ";
            cin >> accNo;

            for (auto &c : customers) {
                if (c.account.accountNumber == accNo) {
                    cout << "Enter amount: ";
                    cin >> amount;
                    c.account.deposit(amount);
                }
            }
        }

        else if (choice == 3) {
            int accNo;
            double amount;

            cout << "Enter account number: ";
            cin >> accNo;

            for (auto &c : customers) {
                if (c.account.accountNumber == accNo) {
                    cout << "Enter amount: ";
                    cin >> amount;
                    c.account.withdraw(amount);
                }
            }
        }

        else if (choice == 4) {
            int fromAcc, toAcc;
            double amount;

            cout << "Enter sender account number: ";
            cin >> fromAcc;

            cout << "Enter receiver account number: ";
            cin >> toAcc;

            cout << "Enter amount: ";
            cin >> amount;

            Account *from = nullptr;
            Account *to = nullptr;

            for (auto &c : customers) {
                if (c.account.accountNumber == fromAcc)
                    from = &c.account;

                if (c.account.accountNumber == toAcc)
                    to = &c.account;
            }

            if (from && to)
                transferMoney(*from, *to, amount);
            else
                cout << "Account not found!\n";
        }

        else if (choice == 5) {
            int accNo;
            cout << "Enter account number: ";
            cin >> accNo;

            for (auto &c : customers) {
                if (c.account.accountNumber == accNo)
                    c.displayInfo();
            }
        }

        else if (choice == 6) {
            int accNo;
            cout << "Enter account number: ";
            cin >> accNo;

            for (auto &c : customers) {
                if (c.account.accountNumber == accNo)
                    c.account.showTransactions();
            }
        }

    } while (choice != 0);

    cout << "Thank you for using the Banking System!\n";

    return 0;
}