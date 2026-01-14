#include <limits>
#include <iomanip>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> history;
string email, password, fname, mname, lname, acc_email, acc_password;
string rec_email, rec_password;
string acc_em, acc_pass;
double balance = 0;
double depositAmount, withdrawAmount, receiverBalance;
const int depositLimit = 100000;

int confirm = 0;
int user_status;
int max_choice_amt = 3;
int reset = 99;
int confirmation = 1;
int amount;
int func_choice;
int max_func = 9; // 9 lang dahil hindi kasama yung log-out
int attempts = 4;

void createAccount()
{
    do
    {
        cout << "Creating New User:\n ";
        cout << "Enter your First Name: ";
        cin >> fname;
        cout << "Enter your Last Name: ";
        cin >> lname;
        cout << "Enter your email address: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;
        do
        {
            cout << "Proceed:\n 1. Yes\n 2. Edit" << endl;
            cout << "Enter your choice: ";
            cin >> confirm;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 1 or 2." << endl;
                confirm = 0;
            }
        } while (confirm != 1 && confirm != 2);
    } while (confirm == 2);
    acc_email = email;
    acc_password = password;
    cout << "Account Created" << endl;
}

void deposit()
{
    do
    {
        cout << "Enter amount to deposit: ";
        cin >> depositAmount;

        if (cin.fail())
        {
            cout << "Invalid character. Please input a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (depositAmount > depositLimit)
        {
            cout << "Deposit amount exceeds the limit of " << depositLimit << " PHP\n";
        }
        else if (depositAmount <= 0)
        {
            cout << "Invalid deposit amount\n";
        }
        else
        {
            balance += depositAmount;
            cout << "Deposit successful\n";

            ostringstream stream;
            stream << fixed << setprecision(2) << depositAmount;
            history.push_back("Deposited: " + stream.str());
            break;
        }
    } while (true);
}

void withdraw()
{
    string inputPass;
    attempts = 4;
    do
    {
        cout << "Enter your Password: ";
        cin >> inputPass;

        if (inputPass != acc_password)
        {
            attempts--;
            cout << "Incorrect Password. Attempts remaining: " << attempts << "\n";
            if (attempts == 0)
            {
                cout << "Access Denied.\n";
                return;
            }
        }
    } while (inputPass != acc_password);

    cout << "User authorized. Current balance: " << balance << " PHP\n";

    do
    {
        cout << "Enter amount to withdraw: ";
        cin >> withdrawAmount;

        if (cin.fail())
        {
            cout << "Invalid character. Please input a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (withdrawAmount > balance)
        {
            cout << "Insufficient funds\n";
        }
        else if (withdrawAmount <= 0)
        {
            cout << "Invalid withdrawal amount\n";
        }
        else
        {
            balance -= withdrawAmount;
            cout << "Withdrawal successful\n";

            ostringstream stream;
            stream << fixed << setprecision(2) << withdrawAmount;
            history.push_back("Withdrawn: " + stream.str());
            break;
        }
    } while (true);
}

void transfer()
{
    string inputPass;
    attempts = 4;

    do
    {
        cout << "Enter your Password: ";
        cin >> inputPass;

        if (inputPass != acc_password || inputPass != password)
        {
            attempts--;
            cout << "Incorrect Password. Attempts remaining: " << attempts << "\n";
            if (attempts == 0)
            {
                cout << "Access Denied.\n";
                return;
            }
        }
    } while (inputPass != acc_password);

    cout << "Enter receiver email: ";
    cin >> rec_email;

    do
    {
        cout << "Enter amount to transfer: ";
        cin >> withdrawAmount;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (withdrawAmount > balance)
        {
            cout << "Insufficient funds\n";
        }
        else if (withdrawAmount <= 0)
        {
            cout << "Invalid transfer amount\n";
        }
        else
        {
            balance -= withdrawAmount;
            cout << "Transfer successful to " << rec_email << "\n";

            ostringstream stream;
            stream << fixed << setprecision(2) << withdrawAmount;
            history.push_back("Transferred: " + stream.str() + " to " + rec_email);
            break;
        }
    } while (true);
}
void checkBalance(double bal)
{
    cout << "Current Balance: Php " << fixed << setprecision(2) << bal << endl;
}

void checkInterest()
{
    double invested, time;
    const double rate = 0.0625 / 100;
    do
    {
        cout << "\nInterest Calculator\n0.0625 annual rate\nEnter the Amount you want to Invest: ";
        cin >> invested;
        cout << "Enter Time (Years): ";
        cin >> time;
         if (cin.fail() || time <= 0 || invested <= 0 || time <= 0 && invested <= 0)
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        time = 0;
                        invested = 0;
                        cout << "\nInvalid Input" << endl;
                    }

        else{
            double earned = invested * rate * time;
            cout << fixed << setprecision(2) << "Interest Earned: Php " << earned << endl;
            cout << "Final Total: Php " << (invested + earned) << "\n"
                 << endl;
        }
    }while (time <=0 || invested <= 0);
}

void showTransactionHistory()
{
    if (history.empty())
    {
        cout << "No transactions yet.\n"
             << endl;
        return;
    }
    for (string entry : history)
    {
        cout << entry << endl;
    }
}

void resetInfo()
{
    
    cout << "Update Account:\nEnter new email: ";
    cin >> email;
    cout << "Enter new password: ";
    cin >> password;
    acc_email = email;
    acc_password = password;
    cout << "Account updated successfully.\n"<< endl;
}

void deleteAccount()
{
    int delConfirm;
    cout << "Are you sure? (1. Yes / 2. No): ";
    cin >> delConfirm;
    if (delConfirm == 1)
    {
        acc_email = "";
        acc_password = "";
        cout << "Account deleted.\n"
             << endl;
    }
}

int main()
{
    do
    {
        cout << "User Status:\n";
        cout << "1. New User\n";
        cout << "2. Existing User\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> user_status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            user_status = reset;
        }
        switch (user_status)
        {
        case 1:
            createAccount();
            user_status = reset;
            break;

        case 2:
            do
            {
                cout << "Log In Your Account:\n ";
                cout << "Enter your email: ";
                cin >> email;
                cout << "Enter your password: ";
                cin >> password;
            } while (email != acc_email && password != acc_password || email != acc_email || password != acc_password);
            do
            {
                if (email == acc_email && password == acc_password)
                {
                    cout << "1. Deposit Money" << endl;
                    cout << "2. Withdraw Money" << endl;
                    cout << "3. Check Balance" << endl;
                    cout << "4. Calculate Interest" << endl;
                    cout << "5. Update Account Info" << endl;
                    cout << "6. Delete Account" << endl;
                    cout << "7. Transaction History" << endl;
                    cout << "8. Transfer Money" << endl;
                    cout << "9. Account Info" << endl;
                    cout << "10. Log-Out" << endl;
                    cout << "Enter your choice:\n";
                    cin >> func_choice;
                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        func_choice = reset;
                    }
                    switch (func_choice)
                    {
                    case 1:
                        deposit();
                        break;
                    case 2:
                        withdraw();
                        break;
                    case 3:
                        checkBalance(balance);
                        break;
                    case 4:
                        checkInterest();
                        break;
                    case 5:
                        resetInfo();
                        break;
                    case 6:
                        deleteAccount();
                        break;
                    case 7:
                        showTransactionHistory();
                        break;
                    case 8:
                        transfer();
                        break;
                    case 9:
                        cout << "First Name: " + fname << endl;
                        cout << "Last Name: " + lname + "\n"
                             << endl;
                        break;
                    case 10:
                        user_status = reset;
                        break;

                    default:
                        continue;
                    }
                }
            } while (func_choice != 10);
            break;

        case 3:
            return 0;
        }
    } while (user_status >= max_choice_amt || user_status <= 0);
    return 0;
}