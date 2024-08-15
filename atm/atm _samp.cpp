#include <bits/stdc++.h>
//#include <pqxx/pqxx>
using namespace std;

class account {
    string password;
    int balance;
    vector<string> history;

public:
    account() : password(""), balance(0) {}

    account(const string& pass) : password(pass), balance(0) {}

    bool vali_password(const string& pass) const {
        return pass == password;
    }

    void val_balance() const {
        cout << "Your balance is: " << balance << endl;
    }

    void add_amount(int amount) {
        balance += amount;
        history.push_back("Added: " + to_string(amount));
        cout << amount << " added to your account." << endl;
    }

    void withdraw_amount(int amount) {
        if (amount > balance) {
            cout << "Insufficient balance" << endl;
        } else {
            balance -= amount;
            history.push_back("Withdrew: " + to_string(amount));
            cout << amount << " withdrawn from your account." << endl;
        }
    }

    void show_history() const {
        cout << "Transaction history:" << endl;
        for (const string& entry : history) {
            cout << entry << endl;
        }
    }
};

class atm {
    map<string, account> users;

    void atm_menu() const {
        cout << "********************************************************************" << endl;
        cout << "Click: 1 to check your balance" << endl;
        cout << "Click: 2 to add amount to your wallet" << endl;
        cout << "Click: 3 to withdraw amount" << endl;
        cout << "Click: 4 to view transaction history" << endl;
        cout << "Click: 5 to Exit" << endl;
    }

    bool validate_user(const string& user) {
        if (users.find(user) == users.end()) {
            cout << "Account not found" << endl;
            return false;
        }
        string password;
        int attempts = 3;

        account& acc = users[user];
        while (attempts--) {
            cout << "Enter your password: ";
            cin >> password;
            if (acc.vali_password(password)) {
                return true;
            } else if (attempts > 0) {
                cout << "You have " << attempts << " attempts left" << endl;
            } else {
                cout << "Sorry, account is locked" << endl;
                return false;
            }
        }
        return false;
    }

public:
    void add_user() {
        cout << "***************************************" << endl;
        cout << "Welcome to Our Bank" << endl;
        cout << "Click: 1 to Register as a new user" << endl;
        cout << "Click: 2 if Already a user" << endl;
        int op;
        cin >> op;
        switch (op) {
            case 1: {
                string username;
                string password;
                cout << "Enter your Username: "<< endl;
                cin >> username;
                cout << "Enter your Password: "<< endl;
                cin >> password;
                users[username] = account(password);
                cout << "Account Created Successfully" << endl;
                break;
            }
            case 2:
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    void run() {
        string username;
        cout << "Enter your username: " << endl;
        cin >> username;

        if (!validate_user(username)) {
            return;
        }
        account& acc = users[username];
        while (true) {
            atm_menu();
            int options;
            cin >> options;
            // Clear screen command for Windows
            system("cls"); // Note: This is platform-specific, use with caution

            switch (options) {
                case 1:
                    acc.val_balance();
                    break;
                case 2: {
                    int amount;
                    cout << "Enter amount to add: ";
                    cin >> amount;
                    acc.add_amount(amount);
                    break;
                }
                case 3: {
                    int amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    acc.withdraw_amount(amount);
                    break;
                }
                case 4:
                    acc.show_history();
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        }
    }
};

int main() {
    atm union_bank;
    union_bank.add_user();

    union_bank.run();

    return 0;
}
