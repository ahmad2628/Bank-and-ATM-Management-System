#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<conio.h>
#include<cstdlib>
using namespace std;


//  Bank & ATM Management System

struct Account
{
    string id, name, fname, address, pin, number;
    float balance;
};

const string DATA_FILE = "bank.txt";
const string BILL_FILE = "bill.txt";

// ---------------- Utility Functions ----------------

// Reads 'length' characters from keyboard without echoing them (shows * instead)
string maskedInput(int length, const string &prompt)
{
    cout << prompt;
    string value;
    for (int i = 0; i < length; i++)
    {
        char ch = getch();
        value += ch;
        cout << "*";
    }
    return value;
}

// Loads every account record from bank.txt into memory
vector<Account> loadAccounts()
{
    vector<Account> accounts;
    ifstream file(DATA_FILE.c_str());
    Account a;
    while (file >> a.id >> a.name >> a.fname >> a.address >> a.pin >> a.number >> a.balance)
    {
        accounts.push_back(a);
    }
    file.close();
    return accounts;
}

// Overwrites bank.txt with the current in-memory account list
void saveAccounts(const vector<Account> &accounts)
{
    ofstream file(DATA_FILE.c_str(), ios::trunc);
    for (size_t i = 0; i < accounts.size(); i++)
    {
        const Account &a = accounts[i];
        file << a.id << " " << a.name << " " << a.fname << " " << a.address << " "
             << a.pin << " " << a.number << " " << a.balance << endl;
    }
    file.close();
}

// Returns index of account with given id, or -1 if not found
int findAccountIndex(const vector<Account> &accounts, const string &id)
{
    for (size_t i = 0; i < accounts.size(); i++)
        if (accounts[i].id == id)
            return (int)i;
    return -1;
}

void pause()
{
    cout << "\n\nPress any key to continue...";
    getch();
}

// ---------------- Bank Class ----------------

class Bank
{
public:
    void menu();
    void bank_management();
    void atm_management();
    void new_user();
    void already_user();
    void deposit();
    void withdraw();
    void transfer();
    void payment();
    void user_balance();
    void withdraw_atm();
    void check_detail();
};

void intro()
{
    cout << "\n\n\n\n\n\t";
    for (int i = 1; i <= 60; i++) cout << "*";
    cout << "\n\t ";
    for (int i = 1; i <= 58; i++) cout << "*";
    cout << "\n\t  ";
    for (int i = 1; i <= 56; i++) cout << "*";
    cout << "\n\n\t\t\t\tWelcome To The\n\n\t\t\tBank & Atm Management System\n\n\t   ";
    for (int i = 1; i <= 55; i++) cout << "*";
    cout << "\n\t  ";
    for (int i = 1; i <= 57; i++) cout << "*";
    cout << "\n\t ";
    for (int i = 1; i <= 59; i++) cout << "*";
    getch();
    system("cls");
}

// ---------------- Main Control Panel ----------------
void Bank::menu()
{
    int choice = 0;
    do
    {
        system("cls");
        cout << "\t\t*****************************" << endl;
        cout << "\t\t*\tCONTROL  PANEL      *" << endl;
        cout << "\t\t*****************************" << endl;
        cout << "\n1. BANK MANAGEMENT" << endl;
        cout << "2. ATM MANAGEMENT" << endl;
        cout << "3. LOG OUT " << endl;
        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            cout << "\n\t\t**************************" << endl;
            cout << "\t\t*\tADMIN LOGIN      *" << endl;
            cout << "\t\t**************************" << endl;
            string email;
            cout << "\nEnter E-MAIL : ";
            cin >> email;
            string password = maskedInput(8, "\nEnter PASSWORD : ");

            if (email == "m.ahmad@gmail.com" && password == "ahmad123")
            {
                bank_management();
            }
            else
            {
                cout << "\n\nInvalid E-MAIL or PASSWORD!!!";
                pause();
            }
            break;
        }
        case 2:
            atm_management();
            break;
        case 3:
            cout << "\nLogging out...\n";
            break;
        default:
            cout << "\nInvalid choice!!!" << endl;
            cout << "Please try again..." << endl;
            pause();
        }
    } while (choice != 3);
}

// ---------------- Bank Management Menu ----------------
void Bank::bank_management()
{
    int choice = 0;
    do
    {
        system("cls");
        cout << "\n\tBANK MANAGEMENT SYSTEM" << endl;
        cout << "\n1.  NEW USER " << endl;
        cout << "2.  ALREADY USER " << endl;
        cout << "3.  DEPOSIT OPTION " << endl;
        cout << "4.  WITHDRAW OPTION " << endl;
        cout << "5.  TRANSFER OPTION " << endl;
        cout << "6.  BILL PAYMENT OPTION " << endl;
        cout << "7.  GO BACK " << endl;
        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1: new_user();     pause(); break;
        case 2: already_user(); pause(); break;
        case 3: deposit();      pause(); break;
        case 4: withdraw();     pause(); break;
        case 5: transfer();     pause(); break;
        case 6: payment();      pause(); break;
        case 7: break; // go back to main menu
        default:
            cout << "\nInvalid choice!!!" << endl;
            cout << "Please try again..." << endl;
            pause();
        }
    } while (choice != 7);
}

// ---------------- ATM Management Menu ----------------
void Bank::atm_management()
{
    int choice = 0;
    do
    {
        system("cls");
        cout << "\n\t\tATM MANAGEMENT SYSTEM" << endl;
        cout << "\n1. USER LOGIN & CHECK BALANCE " << endl;
        cout << "2. WITHDRAW AMOUNT " << endl;
        cout << "3. ACCOUNT DETAILS " << endl;
        cout << "4. GO BACK " << endl;
        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1: user_balance();  pause(); break;
        case 2: withdraw_atm();  pause(); break;
        case 3: check_detail();  pause(); break;
        case 4: break; // go back to main menu
        default:
            cout << "\nInvalid choice!!!" << endl;
            cout << "Please try again..." << endl;
            pause();
        }
    } while (choice != 4);
}

// ---------------- New User (PIN only, no password stored) ----------------
void Bank::new_user()
{
    system("cls");
    vector<Account> accounts = loadAccounts();
    Account a;

    cout << "\n\t\tAdd New User" << endl;
    cout << "\nEnter User ID : ";
    cin >> a.id;

    if (findAccountIndex(accounts, a.id) != -1)
    {
        cout << "\n\tThis User ID already exists! Please use a different ID.";
        return;
    }

    cout << "\nEnter Name : ";
    cin >> a.name;
    cout << "\nEnter Father Name : ";
    cin >> a.fname;
    cout << "\nEnter the Address : ";
    cin >> a.address;
    a.pin = maskedInput(4, "\nEnter Pin Code (4 digit) : ");
    cout << "\n\nEnter Phone No. : ";
    cin >> a.number;
    cout << "\nInitial Balance : ";
    cin >> a.balance;

    if (a.balance < 0)
    {
        cout << "\n\tInvalid balance amount!!!";
        return;
    }

    accounts.push_back(a);
    saveAccounts(accounts);

    cout << "\n\n\tNew User Account Created Successfully..." << endl;
}

// ---------------- View Existing Account (PIN only) ----------------
void Bank::already_user()
{
    system("cls");
    vector<Account> accounts = loadAccounts();
    string t_id;

    cout << "\n\t\tAlready User Account" << endl;
    cout << "\nUser ID : ";
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx != -1 && accounts[idx].pin == t_pin)
    {
        Account &a = accounts[idx];
        system("cls");
        cout << "\n\t\tAlready User Account" << endl;
        cout << "\nUser ID : " << a.id << endl;
        cout << "Name : " << a.name << endl;
        cout << "Father Name : " << a.fname << endl;
        cout << "Address : " << a.address << endl;
        cout << "Phone No. : " << a.number << endl;
        cout << "Current Balance : " << a.balance << endl;
    }
    else
    {
        cout << "\n\tInvalid User ID or Pin Code...";
    }
}

// ---------------- Deposit (PIN only) ----------------
void Bank::deposit()
{
    system("cls");
    vector<Account> accounts = loadAccounts();
    string t_id;

    cout << "\n\t\tDeposit Amount" << endl;
    cout << "\nUser ID : ";
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx == -1 || accounts[idx].pin != t_pin)
    {
        cout << "\n\tInvalid User ID or Pin Code...";
        return;
    }

    cout << "\n\nName : " << accounts[idx].name << endl;
    cout << "Current Balance : " << accounts[idx].balance << endl;
    cout << "Enter Amount for Deposit : ";
    float amt;
    cin >> amt;

    if (amt <= 0)
    {
        cout << "\n\tInvalid amount!!!";
        return;
    }

    accounts[idx].balance += amt;
    saveAccounts(accounts);

    cout << "\n\tAmount " << amt << " Successfully Deposited..." << endl;
    cout << "Now your Current Balance is : " << accounts[idx].balance << endl;
}

// ---------------- Withdraw - Bank Management (PIN only) ----------------
void Bank::withdraw()
{
    system("cls");
    vector<Account> accounts = loadAccounts();
    string t_id;

    cout << "\n\t\tWithdraw Amount" << endl;
    cout << "\nUser ID : ";
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx == -1 || accounts[idx].pin != t_pin)
    {
        cout << "\n\tInvalid User ID or Pin Code...";
        return;
    }

    cout << "\n\nCurrent Balance : " << accounts[idx].balance << endl;
    cout << "Enter Amount for Withdraw : ";
    float amt;
    cin >> amt;

    if (amt <= 0)
    {
        cout << "\n\tInvalid amount!!!";
        return;
    }

    if (amt <= accounts[idx].balance)
    {
        accounts[idx].balance -= amt;
        saveAccounts(accounts);
        cout << "\n\tAmount " << amt << " Successfully Withdrawn..." << endl;
        cout << "Now your Current Balance is : " << accounts[idx].balance << endl;
    }
    else
    {
        cout << "\n\tInsufficient Balance! Current Balance is : " << accounts[idx].balance << endl;
    }
}

// ---------------- Transfer (PIN only, logic bug fixed) ----------------
void Bank::transfer()
{
    system("cls");
    vector<Account> accounts = loadAccounts();

    cout << "\n\t\tPayment Transfer" << endl;
    cout << "\nSender User ID : ";
    string s_id;
    cin >> s_id;
    string s_pin = maskedInput(4, "\nEnter Sender Pin Code : ");

    cout << "\n\nReceiver User ID : ";
    string r_id;
    cin >> r_id;

    cout << "\nEnter Transaction Amount : ";
    float amt;
    cin >> amt;

    int sIdx = findAccountIndex(accounts, s_id);
    int rIdx = findAccountIndex(accounts, r_id);

    if (sIdx == -1 || accounts[sIdx].pin != s_pin)
    {
        cout << "\n\tInvalid Sender ID or Pin Code!!!";
        return;
    }
    if (rIdx == -1)
    {
        cout << "\n\tReceiver ID not found!!!";
        return;
    }
    if (s_id == r_id)
    {
        cout << "\n\tSender and Receiver account cannot be the same!!!";
        return;
    }
    if (amt <= 0 || amt > accounts[sIdx].balance)
    {
        cout << "\n\tInsufficient Balance or Invalid Amount!!!";
        return;
    }

    accounts[sIdx].balance -= amt;
    accounts[rIdx].balance += amt;
    saveAccounts(accounts);

    cout << "\n\n\tYour Transaction Successfully Completed..." << endl;
    cout << "Your Remaining Balance is : " << accounts[sIdx].balance << endl;
}

// ---------------- Bill Payment (PIN only, rename bug fixed) ----------------
void Bank::payment()
{
    system("cls");
    vector<Account> accounts = loadAccounts();

    cout << "\n\t\tBills Payment" << endl;
    cout << "\nUser ID : ";
    string t_id;
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx == -1 || accounts[idx].pin != t_pin)
    {
        cout << "\n\tInvalid User ID or Pin Code!!!";
        return;
    }

    cout << "\n\nBill Name : ";
    string b_name;
    cin >> b_name;
    cout << "\nBill Amount : ";
    float amt;
    cin >> amt;

    if (amt <= 0 || amt > accounts[idx].balance)
    {
        cout << "\n\tInsufficient Balance or Invalid Amount!!!";
        return;
    }

    accounts[idx].balance -= amt;
    saveAccounts(accounts);

    ofstream billFile(BILL_FILE.c_str(), ios::app);
    billFile << t_id << " " << b_name << " " << amt << endl;
    billFile.close();

    cout << "\n\t\t" << b_name << " Bill Paid Successfully..." << endl;
    cout << "Your Remaining Balance is : " << accounts[idx].balance << endl;
}

// ---------------- ATM: User Login & Check Balance (PIN only) ----------------
void Bank::user_balance()
{
    system("cls");
    vector<Account> accounts = loadAccounts();

    cout << "\n\t\tUser Login & Check Balance" << endl;
    cout << "\nUser ID : ";
    string t_id;
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx != -1 && accounts[idx].pin == t_pin)
    {
        cout << "\n\n\t\tYour Current Balance is : " << accounts[idx].balance << endl;
    }
    else
    {
        cout << "\n\n\t\tUser ID or Pin Code Invalid...";
    }
}

// ---------------- ATM: Withdraw (PIN only) ----------------
void Bank::withdraw_atm()
{
    system("cls");
    vector<Account> accounts = loadAccounts();

    cout << "\n\t\tWithdraw Amount" << endl;
    cout << "\nUser ID : ";
    string t_id;
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx == -1 || accounts[idx].pin != t_pin)
    {
        cout << "\n\tUser ID or Pin Code Invalid...";
        return;
    }

    cout << "\n\nCurrent Balance : " << accounts[idx].balance << endl;
    cout << "Enter Amount for Withdraw : ";
    float amt;
    cin >> amt;

    if (amt <= 0)
    {
        cout << "\n\tInvalid amount!!!";
        return;
    }

    if (amt <= accounts[idx].balance)
    {
        accounts[idx].balance -= amt;
        saveAccounts(accounts);
        cout << "\n\tAmount " << amt << " Successfully Withdrawn..." << endl;
        cout << "Now, Your Current Balance is : " << accounts[idx].balance << endl;
    }
    else
    {
        cout << "\n\tYour Current Balance " << accounts[idx].balance << " is insufficient..." << endl;
    }
}

// ---------------- ATM: Account Details (PIN only) ----------------
void Bank::check_detail()
{
    system("cls");
    vector<Account> accounts = loadAccounts();

    cout << "\n\t\tAccount Details" << endl;
    cout << "\nUser ID : ";
    string t_id;
    cin >> t_id;
    string t_pin = maskedInput(4, "\nEnter Pin Code : ");

    int idx = findAccountIndex(accounts, t_id);
    if (idx != -1 && accounts[idx].pin == t_pin)
    {
        Account &a = accounts[idx];
        system("cls");
        cout << "\n\t\tAccount Details" << endl;
        cout << "\nUser ID : " << a.id << endl;
        cout << "Name : " << a.name << endl;
        cout << "Father Name : " << a.fname << endl;
        cout << "Address : " << a.address << endl;
        cout << "Phone No. : " << a.number << endl;
        cout << "Current Balance : " << a.balance << endl;
    }
    else
    {
        cout << "\n\tUser ID or Pin Code Invalid...";
    }
}

int main()
{
    Bank obj;
    intro();
    obj.menu();
    return 0;
}