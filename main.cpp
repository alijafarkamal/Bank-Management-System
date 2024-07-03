//23L-0815 // 23L-0761 // 23L-0639 // 23L-0584
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
const string USERS_FILE = "users.txt";
const string COMPANIES_FILE = "companies.txt";
const string EMPLOYEES_FILE = "companies_employees.txt";
const string ADMIN_FILE = "admin.txt";
const string TRANSACTIONS_FILE = "transactions.txt";
const string CARDS_FILE = "cards.txt";
class Account;
class CompanyClient;
class BankingEmployee;
class UserClient;
string account_freeze;
void company_client_register();
void registerUser();
void manageUserAccount(UserClient& user);
void manageCompanyAccount(CompanyClient& company);
bool bankingEmployeeLogin();
void loginUser();
void company_client_login();
template <typename T>
void show_trans(T show_transaction, T id) {
    ifstream file(TRANSACTIONS_FILE);
    cout << string(100, '-') << endl;
    while (getline(file, show_transaction)) {
        if (show_transaction.find(id)) {
            cout << endl << show_transaction;
        }
        show_transaction.empty();
    }
}

bool char_checker(string charr) {
    if (charr.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != string::npos)
        return true;
    else return false;
}
bool num_checker(string num) {
    if (num.find_first_of("0123456789") != string::npos) return true;
    else return false;
}
class Account {
public:
    string userID;
    string username;
    string address;
    string cnic;
    string password;
    double balance;
    string type;
public:
    Account(string userID, string username, string address, string cnic, string password, double balance)
        : userID(userID), username(username), address(address), cnic(cnic), password(password), balance(balance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;  // Withdrawal successful
        }
        return false;  // Insufficient funds
    }

    virtual void transfer(double amount, string recipientID) {
        // Transfer funds to another account
    }

    virtual void displayBalance() {
        cout << "Balance: " << balance << " PKR" << endl;
    }

    virtual void displayTransactions() {
        ifstream file(TRANSACTIONS_FILE);
        if (file.is_open()) {
            string transaction;
            while (getline(file, transaction)) {
                cout << transaction << endl;
            }
            file.close();
        }
        else {
            cout << "Unable to open transactions file." << endl;
        }
    }
};

class UserClient : public Account {
public:
    double dailyWithdrawalLimit;
    string cardNumber;
    string pin;

public:
    UserClient(string userID, string username, string address,
        string cnic, string password, double balance, double dailyWithdrawalLimit)
        : Account(userID, username, address, cnic, password,
            balance), dailyWithdrawalLimit(dailyWithdrawalLimit) {
    label3:
        cout << endl;
        cout << string(100, '-') << endl;
        pin.empty();
        int num;
        cardNumber.empty();
        for (int i = 0; i < 16; i++)
        {
            num = rand() % 10;
            cardNumber += to_string(num);
        }
    label1:
        cout << "Enter a pin number \n";
        cin >> pin;
        if (char_checker(pin)) { cout << "Wrong pin\n";  goto label1; }
        if (dailyWithdrawalLimit <= 100000) type = "Bronze";
        else type = "Gold";
        ofstream file(CARDS_FILE, ios::app);
        file << userID << ", " << cardNumber << ", " << pin << "\n";
        file.close();
        int reply(0);
        cout << "\nYour account has been opened of type " << type << endl;
        cout << "Do you want to make another credit card.\n Press 1 to make or press any other key to continue\n";
        cin >> reply;
        if (reply == 1) goto label3;
    }
    void recordTransaction(double amount, string transactionType) {
        string date;
        cout << "Enter date: ";
        cin >> date;
        ofstream file(TRANSACTIONS_FILE, ios::app);
        file << date << ", " << userID << ", " << amount << ", " << transactionType << endl;
        file.close();
    }
    void deposit(double amount) override {
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        Account::deposit(amount);
        string date;
        cout << "Enter date \n";
        cin >> date;
        ofstream file(TRANSACTIONS_FILE, ios::app);
        //Account::withdraw(amount);
        file << date << ", " << userID << ", " << amount << ", " << "deposit" << "\n";
        file.close();
        // Record transaction
    }

    bool withdraw(double amount) override {
        // Check withdrawal limit and balance
        //if(!with_draw(amount,dailyWithdrawalLimit))
        int size = account_freeze.find(userID);
        if (size != string::npos) return false;
        if (amount > dailyWithdrawalLimit) {
            cout << "You cannot withdraw amount greater than your daily withdraw limit\n";
            return 0;
        }
        if (balance < amount)
        {
            cout << " You cannot withdraw this amount of money as your balance is low\n";
            return 0;
        }
        string date;
        cout << "Enter date \n";
        cin >> date;
        ofstream file(TRANSACTIONS_FILE, ios::app);
        Account::withdraw(amount);
        file << date << ", " << userID << ", " << amount << ", " << "withdraw" << "\n";
        file.close();
        return true;
        // Record transaction
    }
    void transfer(double amount, string recipientID) override {
        int timer(3);
    label9:
        if (timer == 0) account_freeze += userID + "\n";
     while(timer>0){  
        string pin_num;
        cout << "Enter 4 digit pin of the card upon which you want to make this transaction \n";
        cin >> pin_num;
        string pin_match;
        ifstream pin_file(CARDS_FILE); int pin_checker(-1);
        while (getline(pin_file, pin_match)) {
            pin_checker = pin_match.find(pin_num);
        }
        if (pin_checker == string::npos) {
            cout << "Pin number not found\n Again input\n";
            timer--;
            goto label9;
        }
        else break;

    }
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        int size_len = account_freeze.find(recipientID);
        if (size_len != string::npos) return; // corrected variable name
    
        ofstream file(TRANSACTIONS_FILE, ios::app);
        string recipient_data;
        ifstream user(USERS_FILE);   
        bool recipientFound = false; // Track if recipientID is found
        while (getline(user, recipient_data)) {
            cout << recipient_data << endl;
            if (recipient_data.find(recipientID) != string::npos) {
                recipientFound = true;
                break; // Exit loop if recipientID is found
            }
        }
        if (!recipientFound) {
            cout << "Recipient ID not found." << endl;
            return; // Exit function if recipientID is not found
        }
        string date;
        cout << "Enter date: ";
        cin >> date;
        int length = recipient_data.find(recipientID);
        int end_length = recipient_data.find('\n', length);
        string master_stroke = recipient_data.substr(length, end_length - length);
        int r_length = master_stroke.rfind(',');
        if (r_length != string::npos) {
            string extract = master_stroke.substr(r_length + 1, master_stroke.find('\n', r_length) - r_length - 1);
            extract += to_string(amount);
            withdraw(amount);
            master_stroke.replace(r_length + 1, extract.length(), extract);
            recipient_data.replace(length, master_stroke.length(), master_stroke);
            ofstream user_get(USERS_FILE,ios::app);
            user_get << recipient_data;
            user_get.close();
            file << date << ", " << userID << ", " << amount << ", Transfer" << recipientID << "\n";
            file.close();
        }
    }
 
    void displayTransactions() override {
       // Account::displayTransactions();
        string show_transaction;
        cout << "User specific transactions \n";
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        show_trans(show_transaction, userID);
        // Display user-specific transactions
    }
};
class CompanyClient : public Account {
public:
    string taxNumber;
    double withdraw_limit;
public:
    //id, name, address, tax_number, password, balance
    CompanyClient(string idd, string username, string addr, string tax_no, string pass, double balance, double withdraw)
        : Account(idd, username, addr, tax_no, pass, balance), withdraw_limit(withdraw), taxNumber(tax_no) {
        if (withdraw <= 100000) type = "Bronze";
        else if (withdraw <= 500000) type = "Gold";
        else if (withdraw <= 2000000) type = "business";
        cout << "Your account has been opened of type " << type;
    }
    void deposit(double amount) override {
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        Account::deposit(amount);
        string date;
        cout << "Enter date \n";
        cin >> date;
        ofstream file(TRANSACTIONS_FILE, ios::app);
        file << date << ", " << userID << ", " << amount << ", " << "deposit" << "\n";
        file.close();
        // Record transaction
    }

    bool withdraw(double amount) override {
        int size = account_freeze.find(userID);
        if (size != string::npos) return false;
        if (amount > withdraw_limit) {
            cout << "You cannot withdraw amount greater than you daily withdraw limit\n";
            return 0;
        }
        if (balance < amount)
        {
            cout << " You cannot withdraw this amount of money as your balance is low\n";
            return 0;
        }
        string date;
        cout << "Enter date \n";
        cin >> date;
        ofstream file(TRANSACTIONS_FILE, ios::app);
        Account::withdraw(amount);
        file << date << ", " << userID << ", " << amount << ", " << "withdraw" << "\n";
        file.close();
        return true;
        // Check withdrawal limit and balance
        // Record transaction
    }

    void transfer(double amount, string recipientID) override {
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        int size_len = account_freeze.find(recipientID);
        if (size != string::npos) return;
        string date;
        ofstream file(TRANSACTIONS_FILE, ios::app);
        if (num_checker(recipientID))
        {
            bool True = false;
            ifstream employ(EMPLOYEES_FILE);
            while (getline(employ, date)) {
                int length = date.find(recipientID);
                if (length != string::npos)
                {
                    if (to_string(date[length + 2]) == (userID))
                    {
                        True = true;
                        date.empty();
                        break;
                    }
                }
                date.empty();
            }
            if (!True) {
                cout << "Recipient id not found\n"; return;
            }
            string recipient_data;
            ifstream user(USERS_FILE);
            cout << "Enter date \n";
            cin >> date;
            while (getline(user, recipient_data)) {
                cout << recipient_data << endl;
            }
            int length = recipient_data.find(recipientID);
            int end_length = recipient_data.find('\n', length);
            string master_stroke = recipient_data.substr(length, end_length - length);
            int r_length = master_stroke.rfind(',');
            if (r_length != string::npos) {
                string extract = master_stroke.substr(r_length + 1, master_stroke.find('\n', r_length) - r_length - 1);
                extract += to_string(amount);
                withdraw(amount);
                master_stroke.replace(r_length + 1, extract.length(), extract);
                recipient_data.replace(length, master_stroke.length(), master_stroke);
                ofstream user_get(USERS_FILE,ios::app );
                user_get << recipient_data;
                user_get.close();
                file << date << ", " << userID << ", " << amount << ", Transfer" << recipientID << "\n";
                file.close();
            }
            return;
        }
        // Transfer funds to another user client's account
        // Record transaction
    }

    void displayTransactions() override {
        //Account::displayTransactions();
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        string show_transaction;
        show_trans(show_transaction, userID);
        // Display company-specific transactions
    }
    void requestLoan(double amount) {
        int size = account_freeze.find(userID);
        if (size != string::npos) return;
        cout << "Your request for loan is being proceeded to bank employee\n";
        if (bankingEmployeeLogin()) {
            balance += amount;
            cout << "You have been given loan of Rs." << amount << endl;
        }
        else {
            cout << "Your loan request is rejected \n";
        }

         // Request loan from bank
    }
};

class BankingEmployee {
private:
    string userID;
    string password;
public:
    BankingEmployee(string userID, string password) : userID(userID), password(password) {}

    void viewClientAccounts() {
        ifstream user_file(USERS_FILE); string data;
        cout << "***** Below is the User's data ******\n";
        while (getline(user_file, data)) {
            cout << data << endl;
        }
        cout << "***** Below is the Companies's accounts data ******\n";
        ifstream comp_file(COMPANIES_FILE);
        while (getline(comp_file, data)) {
            cout << data << endl;
        }
        // Display list of all client accounts
    }
    bool approveRejectAccountApplication() {
        string approvement;
        cout << "Do you want to approve this account? (yes/no): ";
        cin >> approvement;
        return (approvement == "yes");
    }

    bool approveRejectLoanRequests() {
        string approvement;
        cout << "Do you want to approve this loan request? (yes/no): ";
        cin >> approvement;
        return (approvement == "yes");
    }
    void viewTransactionHistory(string accountID) {
        ifstream file(TRANSACTIONS_FILE);
        string trans_action;
        while (getline(file, trans_action)) {
            int length = trans_action.find(accountID);
            if (length != string::npos) {
                cout << trans_action << endl;
            }
            trans_action.empty();
        }
        file.close();
        // View transaction history for a specific account
    }
    void freezeOrCloseAccount(string accountID) {
        string account_close;
        string search;
        int account_closure;
        cout << "Press 1 to close or 0 to freeze this account\n";
        cin >> account_closure;
        if (account_closure == 0) {
            account_freeze += accountID + '\n';
        }
        if (account_closure == 1) {
            bool True = false;
            ifstream file(USERS_FILE);
            while (getline(file, search)) {
                account_closure = search.find(accountID);
                if (account_closure == string::npos)
                {
                    account_close += search;
                }
                else True = true;
                search.empty();
            }
            if (True)
            {
                ofstream file_user(USERS_FILE,ios::app );
                file_user << account_close;
                file_user.close();
                return;
            }
            account_close.empty();
            search.empty();
            ifstream file_emp(EMPLOYEES_FILE);
            while (getline(file_emp, search)) {
                account_closure = search.find(accountID);
                if (account_closure == string::npos)
                {
                    account_close += search;
                }
                else True = true;
                search.empty();
            }
            if (True)
            {
                ofstream file_comp(COMPANIES_FILE,ios::app);
                file_comp << account_close;
                file_comp.close();
                return;
            }
            if (!True)
            {
                cout << "      Error! Account id not matched       \n";
                return;
            }
        }
        // Freeze or close an account
    }
};

int main() {
    int choice(0);
    string admin_id, admin_pass;
    cout << endl<< string(100, '-') << endl;

    cout << "Enter admin id \n";
    cin >> admin_id;
    cout << "Enter admin password \n";
    cin >> admin_pass;
    ofstream file("admin.txt");
    file << admin_id << admin_pass;
    file.close();
    system("cls");
    cout << endl << string(100, '-') << endl;
    cout << "\n\t\t****************      Welcome to Bank Management System      ****************" << endl;
    cout << endl;
    cout << string(100, '-') << endl;
    while (choice != -1) {
        cout << "1. Login as User" << endl;
        cout << "2. Register as User" << endl;
        cout << "3. Login as Company's client" << endl;
        cout << "4. Register as Company's client" << endl;
        cout << "5. Login as Banking Employee" << endl;
        cout << "-1. To exit" << endl;
        cout << "Enter your choice: \n";
        cin >> choice;
        cout << string(100, '-') << endl;
        switch (choice) {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            company_client_login();
            break;
        case 4:
            company_client_register();
            break;
        case 5:
            bankingEmployeeLogin();
            break;
        default:
            cout << "Exiting program.........." << endl;
            break;
        }
    }
    system("pause");
    return 0;
}
void company_client_login() {
    string id;
    string password;
    cout << string(100, '-') << endl;
    cout << "Enter company id \n";
    cin >> id;
    cout << "Enter company password \n";
    cin >> password;
    int size = account_freeze.find(id);
    if (size != string::npos) return;
    ifstream file(COMPANIES_FILE);
    string file_data;
    int id_length; int pass_length;
    while (getline(file, file_data))
    {
        id_length = file_data.find(id);
        pass_length = file_data.find(password);

        if (id_length != string::npos && pass_length != string::npos) {
            int id_data = file_data.find('\n', id_length);
            string str_id_data = file_data.substr(id_length, id_data - id_length);
            cout << "Below is your data \n" << str_id_data;
            istringstream str(str_id_data);
            // Declare variables to store the parsed data
            string idd, name, address, tax_no, password; double balance, withdraw_limit;
            // Extract data from the stringstream
            getline(str, idd, ',');
            getline(str, name, ',');
            getline(str, address, ',');
            getline(str, tax_no, ',');
            getline(str, password, ',');
            str >> balance; str.ignore(); str >> withdraw_limit;
            CompanyClient user(idd, name, address, tax_no, password, balance, withdraw_limit);
            manageCompanyAccount(user);
        }
        else {
            cout << "Id or password not found\n";
        }
    }
    return;
}
void company_client_register() {
    string id; string name; string address; string tax_number; string password; double balance;
    double withdrawlimit;
label4:
    cout << string(100, '-') << endl;
    cout << "Enter company id number \n";
    cin >> id;
    ifstream id_file(USERS_FILE);
    string id_getter; int checker(-1);
    while (getline(id_file, id_getter)) {
        checker = id_getter.find(id);
    }
    if (checker != string::npos) {
        cout << "Id matched with user employess \n ";
        goto label4;
    }
    if (char_checker(id))
    {
        cout << "Id incorrect . Input again\n"; goto label4;
    }
    cout << "\nEnter company name \n";
    cin >> name;
    if (num_checker(name)) { cout << "Name incorrect. Input again\n"; goto label4; }
    cout << "\nEnter company address\n";
    cin >> address;
    cout << "\nEnter company taxnumber\n";
    cin >> tax_number;
    if (char_checker(tax_number))
    {
        cout << "Tax number incorrect. Input again\n"; goto label4;
    }
    cout << "\nEnter company password\n";
    cin >> password;
    cout << "\nEnter company balance\n";
    cin >> balance;
    if (balance < 0) { cout << "balance incorrect. Input again\n"; goto label4; }
    double withdraw;
    cout << "Enter company daily withdrawl amount\n";
    cin >> withdraw;
    if (withdraw < 0 || withdraw>2000000) {
        cout << "Wrong input. enter amount between 0 and 2000000\n"; goto label4;
    }
    cout << string(100, '-') << endl;
    ofstream company_user(COMPANIES_FILE, ios::app);
   // ofstream admin(ADMIN_FILE,ios::app);
   // admin << id << ", " << password << "\n";
    company_user << id << "," << name << "," << address << "," << tax_number << "," << password << "," << balance << "\n";
    company_user.close();
   // admin.close();
    cout << "\nNow your request for opening a new account is going to bank employee\n";
    if (bankingEmployeeLogin())
    {
        CompanyClient company(id, name, address, tax_number, password, balance,withdraw);
        cout << "Now you can login ******* Thanks\n";
        manageCompanyAccount(company);
    }
    return;
}
void registerUser() {
    string id; string name; string address; string cnic; string password; double balance; int company_account, withdraw;
label:
    cout << string(100, '-') << endl;
    cout << "Enter your id number \n";
    cin >> id;
    ifstream id_file(EMPLOYEES_FILE);
    string id_getter; int id_checker(-1);
    while (getline(id_file, id_getter)) {
        id_checker = id_getter.find(id);
    }
    if (id_checker != string::npos) {
        cout << "id matched with employees. enter again \n"; goto label;
    }
    if (char_checker(id))
    {
        cout << "Id incorrect. Input again\n"; goto label;
    }
    cout << "\nEnter your name \n";
    cin >> name;
    if (num_checker(name)) { cout << "Name incorrect. Input again\n"; goto label; }
    cout << "\nEnter your address\n";
    cin >> address;
    cout << "\nEnter your CNIC\n";
    cin >> cnic;
    if (char_checker(cnic))
    {
        cout << "cnic incorrect. Input again\n"; goto label;
    }
    cout << "\nEnter your password\n";
    cin >> password;
    cout << "\nEnter your balance\n";
    cin >> balance;
    if (balance < 0) { cout << "balance incorrect. Input again\n"; goto label; }

    cout << "Enter your daily withdrawl amount\n";
    cin >> withdraw;
    if (withdraw < 0 || withdraw>500000) { cout << "Wrong input. enter amount between 0 and 500000\n"; goto label; }
    cout << string(100, '-') << endl;
    ofstream user(USERS_FILE, ios::app);
    //ofstream admin(ADMIN_FILE, ios::app);
    cout << "Now your request for opening a new account is going to bank employee\n";
    user << id << "," << name << "," << address << "," << cnic << "," << password << "," << balance << "," << withdraw << "\n";
   // admin << id << "," << password << "\n";
    user.close();
    //admin.close();
    if (bankingEmployeeLogin())
    {
        cout<<endl << "Your account application has been approved \n";
        ofstream comp_emp(EMPLOYEES_FILE,ios::app);
        comp_emp << id << ", ";
        cout << string(100, '-') << endl;
        cout << "Enter company id whose you are an employee \n";
        cin >> company_account;
        comp_emp << company_account << "\n";
        comp_emp.close();
        UserClient user_client(id, name, address, cnic, password, balance, withdraw);
        cout << "\nNow you can login ******* Thanks\n";
        manageUserAccount(user_client);
    }
    return;
    // Logic to login user
}
void manageUserAccount(UserClient& user) {

    int choice;
    double amount;
    string idd;
    ////system("CLS");
    cout << string(100, '-') << endl;
    cout << "You have successfully entered as the admin of your account\n";
    do {
        cout << "\nUser Client Menu:" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Transfer" << endl;
        cout << "4. View Balance" << endl;
        cout << "5. View Transaction History" << endl;
        cout << "-1. To exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << string(100, '-') << endl;
        switch (choice) {
        case 1:
            cout << "Enter deposit amount: ";
            cin >> amount;
            user.deposit(amount);
           break;
        case 2:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            user.withdraw(amount);
            break;
        case 3:
            cout << "Enter amount to be transferred: ";
            cin >> amount;
            cout << "Enter recipient id\n";
            cin >> idd;
            user.transfer(amount, idd);
            break;
        case 4:
            user.displayBalance();
            break;
        case 5:
            user.displayTransactions();
            break;
        default:
            cout << "Exiting......... " << endl;
            break;
        }
    } 
    while (choice != -1);
    ofstream file(USERS_FILE);//ios::app
    string store;
    file << user.userID << "," << user.username << "," << user.address << "," << user.cnic << "," <<
        user.password << "," << user.balance << "," << user.dailyWithdrawalLimit << "\n";
    file.close();

}
//
void manageCompanyAccount(CompanyClient& company) {
    int choice; string id;
    double amount = 0.0; // Assuming initial balance is zero
    do {
        cout << string(100, '-') << endl;
        // Display menu options
        cout << "Company Client Menu:" << endl;
        cout << "1. Deposit Funds" << endl;
        cout << "2. Withdraw Funds" << endl;
        cout << "3. View Account Balance" << endl;
        cout << "4. View Transaction History" << endl;
        cout << "5. Transfer Funds to User Client" << endl;
        cout << "6. Request Loan" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << string(100, '-') << endl;
        switch (choice) {
        case 1: // Deposit Funds
            cout << "Enter amount to deposit: ";
            cin >> amount;
            company.deposit(amount);
            break;
        case 2: // Withdraw Funds
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            company.withdraw(amount);
            break;
        case 3: // View Account Balance
            cout << "Account Balance: " << endl;
            company.displayBalance();
            break;
        case 4: // View Transaction History
            company.displayTransactions();
            break;
        case 5: // Transfer Funds to User Client
            cout << "Enter amount to be transferred: ";
            cin >> amount;
            cout << "Enter recipient id\n";
            cin >> id;
            company.transfer(amount, id);
            break;
        case 6: // Request Loan
            cout << "How much loan do you want to get?\n";
            cin >> amount;
            company.requestLoan(amount);// Placeholder
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != -1);
    ofstream file(COMPANIES_FILE);//ios::app
    file << company.userID << "," << company.username << "," << company.address << "," << company.taxNumber << "," <<
        company.password << "," << company.balance << "," << company.withdraw_limit<< "\n";
    file.close();
    // Logic to manage company account
}
//
bool bankingEmployeeLogin() {
    cout << "\n You have entered as bank employee \n";
    string str; string id;
    ifstream admin(ADMIN_FILE);//admin file reader
    if (!admin.is_open()) cout << "Admin File cannot be opened\n";
    string passWord;
    cout << string(100, '-') << endl;
    cout << "Enter admin ID\n";
    cin >> id;
    cout << "Enter admin password\n";
    cin >> passWord;
    bool True = false;
    while (getline(admin, str)) {
        cout << str << endl;
        int id_length = str.find(id);
        int pass_length = str.find(passWord);
        if (id_length != string::npos && pass_length != string::npos) {
            BankingEmployee bank_emp(id, passWord);
            int choice;
            do
            {
                cout << string(100, '-') << endl;
                string accountID;
                cout << "\nWelcome to the Banking Employee Portal\n\n";
                cout << "Please select an option from the menu:\n";
                cout << "1. View List of All Client Accounts\n";
                cout << "2. Approve or Reject New Account Applications\n";
                cout << "3. Approve or Reject Loan Requests of Companies\n";
                cout << "4. View Transaction History for a Specific Account\n";
                cout << "5. Freeze or Close an Account\n";
                cout << "-1. Exit\n\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << string(100, '-') << endl;
                switch (choice) {
                case 1:
                    bank_emp.viewClientAccounts();
                    True = true;
                    break;
                case 2:
                    if (bank_emp.approveRejectAccountApplication()) {
                        True =  true;
                    }
                    else True =  false;
                    break;
                case 3:
                    if (bank_emp.approveRejectLoanRequests()) {
                        True = true;
                    }
                    else True = false;
                    break;
                case 4:
                    cout << "Enter the account ID: ";
                    cin >> accountID;
                    bank_emp.viewTransactionHistory(accountID);
                    break;
                case 5:
                    cout << "Enter the account ID to manage: ";
                    cin >> accountID;
                    bank_emp.freezeOrCloseAccount(accountID);
                    True = true;
                    break;
                default:
                    cout << "Exiting........\n";
                    break;
                }
            } while (choice != -1);
        }
        str.empty();
    }
    return True;
}
void loginUser() {
    string id;
    string password;
    cout << string(100, '-') << endl;
    cout << "Enter your id \n";
    cin >> id;
    cout << "Enter your password \n";
    cin >> password;
    int size = account_freeze.find(id);
    if (size != string::npos) return;

    ifstream file(USERS_FILE);
    if (!file.is_open()) {
        cout << "\n File cannot be opened\n";
        return; // Exit the function if file cannot be opened
    }

    string file_data;
    while (getline(file, file_data)) {
        size_t id_length = file_data.find(id);
        size_t pass_length = file_data.find(password);
        // Check if both id and password are found
        if (id_length != string::npos && pass_length != string::npos) {
            // Extract data for the user
            string str_id_data = file_data.substr(0, file_data.find('\n'));
            cout << "Below is your data \n" << str_id_data;
            istringstream str(str_id_data);
            string idd, name, address, cnic, password;
            double balance, withdraw_limit;
            // Extract data from the stringstream
            getline(str, idd, ',');
         //   cout << idd<<endl;
            getline(str, name, ',');
          //  cout << name << endl;
            getline(str, address, ',');
          //  cout << address << endl;
            getline(str, cnic, ',');
          //  cout << cnic << endl;
            getline(str, password, ',');
           // cout << password << endl;
            str >> balance; str.ignore();// cout << password << endl;
            str >> withdraw_limit;
          //  cout << withdraw_limit << endl;
            // Create UserClient object
            UserClient user(idd, name, address, cnic, password, balance, withdraw_limit);
            manageUserAccount(user);
            return; // Exit the function since user data is found
        }
    }
    cout << "User data not found. Please check your credentials.\n";
}
