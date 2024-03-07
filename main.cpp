// Include necessary libraries
#include <iostream>
#include <string>

// Using standard namespace for convenience
using namespace std;

// Define the Account class
class Account {
    // Protected attributes accessible by derived classes
protected:
    long int account_No;    // Account number
    string name;            // Account holder's name
    double balance;         // Account balance
    string mobile_No;       // Account holder's mobile number

    // Public methods accessible by all
public:
    // Constructor to initialize account details
    Account(long int accNo, string n, double bal, string mob) : account_No(accNo), name(n), balance(bal), mobile_No(mob) {}

    // Getter methods to access account details
    long int getAccountNo() const {
        return account_No;
    }

    string getName() const {
        return name;
    }

    double getBalance() const {
        return balance;
    }

    string getMobileNo() const {
        return mobile_No;
    }

    // Pure virtual function to display account details (to be implemented by derived classes)
    virtual void display() const = 0;
};

// Define the UserAccount class derived from Account
class UserAccount : public Account {
    // Private attribute specific to UserAccount
private:
    int PIN;    // User's PIN

    // Public methods accessible by all
public:
    // Constructor to initialize user account details
    UserAccount(long int accNo, string n, int pin, double bal, string mob) : Account(accNo, n, bal, mob), PIN(pin) {}

    // Getter method to access user's PIN
    int getPIN() const {
        return PIN;
    }

    // Method to authenticate user using PIN
    bool authenticate(int pin) const {
        return pin == PIN;
    }

    // Method to update user's mobile number
    void setMobile(string mob_prev, string mob_new) {
        if (mob_prev == mobile_No) {
            mobile_No = mob_new;
            cout << endl << "Successfully Updated Mobile no.";
        } else {
            cout << endl << "Incorrect !!! Old Mobile no";
        }
    }

    // Method to withdraw cash from user's account
    void cashWithdraw(int amount) {
        if (amount > 0 && amount < balance) {
            balance -= amount;
            cout << endl << "Please Collect Your Cash";
            cout << endl << "Available Balance :" << balance;
        } else {
            cout << endl << "Invalid Input or Insufficient Balance";
        }
    }

    // Method to display user's account details
    void display() const override {
        cout << endl << "*** User Details are :- ";
        cout << endl << "-> Account no :" << getAccountNo();
        cout << endl << "-> Name      :" << getName();
        cout << endl << "-> Balance   :" << getBalance();
        cout << endl << "-> Mobile No. :" << getMobileNo();
    }
};

// Define the AdminAccount class derived from Account
class AdminAccount : public Account {
    // Public methods accessible by all
public:
    // Constructor to initialize admin account details
    AdminAccount(long int accNo, string n, double bal, string mob) : Account(accNo, n, bal, mob) {}

    // Method to display admin's account details
    void display() const override {
        cout << endl << "*** Admin Details are :- ";
        cout << endl << "-> Account no :" << getAccountNo();
        cout << endl << "-> Name      :" << getName();
        cout << endl << "-> Balance   :" << getBalance();
        cout << endl << "-> Mobile No. :" << getMobileNo();
    }
};

// Define the Bank class to manage user and admin interactions
class Bank {
    // Private attributes to store user and admin accounts
private:
    UserAccount user;
    AdminAccount admin;

    // Public methods accessible by all
public:
    // Constructor to initialize Bank with user and admin accounts
    Bank(UserAccount u, AdminAccount a) : user(u), admin(a) {}

    // Method to run the ATM interface
    void run() {
        int choice = 0;
        
        do {
            system("cls");
            cout << endl << "**** Welcome to ATM *****" << endl;
            cout << endl << "Select Options ";
            cout << endl << "1. Check User Balance";
            cout << endl << "2. Cash withdraw for User";
            cout << endl << "3. Show User Details";
            cout << endl << "4. Update User Mobile no.";
            cout << endl << "5. Show Admin Details";
            cout << endl << "6. Exit" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << endl << "User's Bank balance is :" << user.getBalance();
                    break;

                case 2:
                    int amount;
                    cout << endl << "Enter the amount :";
                    cin >> amount;
                    user.cashWithdraw(amount);
                    break;

                case 3:
                    user.display();
                    break;

                case 4: {
                    string oldMobileNo, newMobileNo;
                    cout << endl << "Enter Old Mobile No. ";
                    cin >> oldMobileNo;
                    cout << endl << "Enter New Mobile No. ";
                    cin >> newMobileNo;
                    user.setMobile(oldMobileNo, newMobileNo);
                    break;
                }

                case 5:
                    admin.display();
                    break;

                case 6:
                    exit(0);
                    break;

                default:
                    cout << endl << "Enter Valid Data !!!";
            }
            cout << endl << "Press any key to continue...";
            cin.ignore();
            cin.get();
        } while (true);
    }
};

// The main function to start the program
int main() {
    // Prompt the user to select user type
    int userType;
    cout << "Welcome to the bank ATM!" << endl;
    cout << "Select User Type:" << endl;
    cout << "1. User" << endl;
    cout << "2. Admin" << endl;
    cin >> userType;

    // Process based on the user type selected
    if (userType == 1) {
        // For user type
        int userPIN;
        cout << "Enter your PIN to log in: ";
        cin >> userPIN;

        // Authenticate user
        UserAccount user(987654321, "Hardik", 1234, 50000, "9370054900");
        if (!user.authenticate(userPIN)) {
            cout << "Invalid PIN. Exiting..." << endl;
            exit(1);
        }

        // Run user interface
        Bank bank(user, AdminAccount(0, "", 0, ""));
        bank.run();
    } else if (userType == 2) {
        // For admin type
        int adminPIN;
        cout << "Enter your PIN to log in as admin: ";
        cin >> adminPIN;

        // Authenticate admin
        AdminAccount admin(123456789, "Admin", 1000000, "9876543210");
        if (adminPIN != 1234) {
            cout << "Invalid admin PIN. Exiting..." << endl;
            exit(1);
        }

        // Run admin interface
        Bank bank(UserAccount(0, "", 0, 0, ""), admin);
        bank.run();
    } else {
        // Invalid user type
        cout << "Invalid user type. Exiting..." << endl;
        exit(1);
    }
    return 0;
}
