#include <iostream>

using namespace std;


#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// GCC BANK - Banking System Assignment
// Gauteng City College
// Introduction to Programming NQF 4

// Structure for storing user details
struct User {
    string name;
    int accountNumber;
    int pin;
    double balance;
};

// Store at least 3 users using an array
User users[3] = {
    {"Thabo", 1001, 1234, 5000.00},
    {"Lerato", 1002, 5678, 3500.00},
    {"Sipho", 1003, 4321, 2500.00}
};

// Function declarations
int login();
void displayMenu();
void deposit(int userIndex);
void withdraw(int userIndex);
void sendCash(int userIndex);
void checkBalance(int userIndex);
int findAccount(int accountNumber);
int getInteger(string message);
double getAmount(string message);


// Main function
int main() {

    int userIndex;
    int choice;

    cout << "=================================\n";
    cout << "          WELCOME TO GCC BANK\n";
    cout << "=================================\n";

    // Login
    userIndex = login();

    if (userIndex == -1) {
        cout << "\nLogin failed. Program closing.\n";
        return 0;
    }

    cout << "\nWelcome, " << users[userIndex].name << "!\n";

    // Banking menu loop
    do {
        displayMenu();

        choice = getInteger("Enter your choice: ");

        switch (choice) {

            case 1:
                deposit(userIndex);
                break;

            case 2:
                withdraw(userIndex);
                break;

            case 3:
                sendCash(userIndex);
                break;

            case 4:
                checkBalance(userIndex);
                break;

            case 5:
                cout << "\nThank you for banking with GCC BANK!\n";
                cout << "Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice! Please select 1-5.\n";
        }

    } while (choice != 5);

    return 0;
}


// Login function
int login() {

    int accountNumber;
    int pin;

    cout << "\n========== ACCOUNT LOGIN ==========\n";

    accountNumber = getInteger("Enter account number: ");

    int index = findAccount(accountNumber);

    if (index == -1) {
        cout << "Account does not exist!\n";
        return -1;
    }

    pin = getInteger("Enter your PIN: ");

    if (pin == users[index].pin) {
        cout << "\nLogin successful!\n";
        return index;
    }
    else {
        cout << "\nIncorrect PIN!\n";
        return -1;
    }
}


// Display banking menu
void displayMenu() {

    cout << "\n=================================\n";
    cout << "             GCC BANK\n";
    cout << "=================================\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "=================================\n";
}


// Deposit function
void deposit(int userIndex) {

    double amount;

    cout << "\n========== DEPOSIT ==========\n";

    amount = getAmount("Enter deposit amount: R");

    if (amount > 0) {

        users[userIndex].balance += amount;

        cout << "\nDeposit successful!\n";
        cout << "Amount deposited: R" << amount << endl;
        cout << "New balance: R"
             << users[userIndex].balance << endl;

    }
    else {
        cout << "\nInvalid amount! Deposit must be more than R0.\n";
    }
}


// Withdraw function
void withdraw(int userIndex) {

    double amount;

    cout << "\n========== WITHDRAW ==========\n";

    amount = getAmount("Enter withdrawal amount: R");

    if (amount <= 0) {

        cout << "\nInvalid amount!\n";

    }
    else if (amount > users[userIndex].balance) {

        cout << "\nInsufficient funds!\n";
        cout << "Your current balance is R"
             << users[userIndex].balance << endl;

    }
    else {

        users[userIndex].balance -= amount;

        cout << "\nWithdrawal successful!\n";
        cout << "Amount withdrawn: R" << amount << endl;
        cout << "Remaining balance: R"
             << users[userIndex].balance << endl;
    }
}


// Find account function
int findAccount(int accountNumber) {

    for (int i = 0; i < 3; i++) {

        if (users[i].accountNumber == accountNumber) {
            return i;
        }
    }

    return -1;
}


// Send cash function
void sendCash(int userIndex) {

    int recipientAccount;
    int recipientIndex;
    double amount;

    cout << "\n========== SEND CASH ==========\n";

    recipientAccount = getInteger("Enter recipient account number: ");

    recipientIndex = findAccount(recipientAccount);

    if (recipientIndex == -1) {

        cout << "\nRecipient account does not exist!\n";
        return;
    }

    if (recipientIndex == userIndex) {

        cout << "\nYou cannot send money to your own account!\n";
        return;
    }

    amount = getAmount("Enter amount to send: R");

    if (amount <= 0) {

        cout << "\nInvalid transfer amount!\n";

    }
    else if (amount > users[userIndex].balance) {

        cout << "\nInsufficient funds for this transfer!\n";

    }
    else {

        users[userIndex].balance -= amount;

        users[recipientIndex].balance += amount;

        cout << "\nTransfer successful!\n";
        cout << "Recipient: " << users[recipientIndex].name << endl;
        cout << "Amount sent: R" << amount << endl;
        cout << "Remaining balance: R"
             << users[userIndex].balance << endl;
    }
}


// Check balance function
void checkBalance(int userIndex) {

    cout << "\n========== ACCOUNT BALANCE ==========\n";

    cout << "Account holder: "
         << users[userIndex].name << endl;

    cout << "Account number: "
         << users[userIndex].accountNumber << endl;

    cout << fixed << setprecision(2);

    cout << "Available balance: R"
         << users[userIndex].balance << endl;

    cout << "=====================================\n";
}


// Integer input validation function
int getInteger(string message) {

    int value;

    while (true) {

        cout << message;

        if (cin >> value) {
            return value;
        }

        cout << "Invalid input! Please enter a whole number.\n";

        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// Money input validation function
double getAmount(string message) {

    double amount;

    while (true) {

        cout << message;

        if (cin >> amount) {

            if (amount > 0) {
                return amount;
            }

            cout << "Please enter an amount greater than zero.\n";
        }
        else {

            cout << "Invalid input! Enter a valid amount.\n";

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


