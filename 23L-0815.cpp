#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<sstream>
using namespace std;
int FinalRecordSize = 0, FinalCardSize = 0, FinaltrasacSize = 0, FinalCompanysize = 0, FinalTotalAccReqs = 0, FinaltotalLoans = 0;

//<----------------------- Classes Implementation------------------------------> 


// 1) users class ----> (Parent/Base) Class of All Client Classes.

class users
{
protected:
	string UniqueID;
	string fullName;
	string address;
	string CNIC;
	string loginID;
	string password;
	string Balance;
public:
	users(const string& name = "", const string& adress = "", string idCard = "", const string& login = "", const string& pass = "", string bal = "")
	{
		// this contructor can be used both as ----> defaut and overloaded .
		fullName = name;
		address = adress;
		CNIC = idCard;
		loginID = login;
		password = pass;
		Balance = bal;
	}
};

// get current time function //

string gettime() {
	time_t currentTime;
	time(&currentTime);
	// Convert the current time to a local time struct
	tm localTime;
	localtime_s(&localTime, &currentTime);
	// Extract the year, month, and day
	int year = localTime.tm_year + 1900; // years since 1900
	int month = localTime.tm_mon + 1;    // months since January [0, 11]
	int day = localTime.tm_mday;         // day of the month [1, 31]       
	string temp = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	return temp;
}

class transactions
{
protected:
	string id;
	string date;
	string amount;
	string transactionType;
	string receiverID;
public:
	transactions() {}
	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, date, ',');
		getline(iss, id, ',');
		getline(iss, amount, ',');
		getline(iss, transactionType, ',');
		getline(iss, receiverID);
	}
	void setid(string ids)
	{
		id = ids;
	}
	void setDate(string tdate)
	{
		date = tdate;
	}
	void setamount(string val)
	{
		amount = val;
	}
	void setTransacType(string type)
	{
		transactionType = type;
	}
	void setReceiverID(string receiver)
	{
		receiverID = receiver;
	}

	void displayData()
	{
		cout << date << "," << id << "," << amount << "," << transactionType << "," << receiverID << endl;

	}
	int getId()
	{
		int x = stoi(id);
		return x;
	}
	friend ostream& operator<<(ostream&, transactions);
};
ostream& operator<<(ostream& fout, transactions obj)
{
	fout << obj.date << "," << obj.id << "," << obj.amount << "," << obj.transactionType << "," << obj.receiverID << endl;
	return fout;
}
void updateTransacData(transactions*& data, int size, transactions obj)
{
	transactions* temp = new transactions[size + 1];
	int i = 0;
	for (i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	temp[i] = obj;
	data = temp;
	temp = nullptr;
	FinaltrasacSize++;
}

class company_employee
{
public:
	string userId;
	string companyID;

	company_employee() {}
	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, userId, ',');
		getline(iss, companyID);
	}
};
company_employee* comp_employees = nullptr;
int comp_empSize = 0;
class cards
{
private:
	string cardNum;
	string pinNumber;
	string id;
public:
	void setCardnum(string s)
	{
		cardNum = s;
	}
	void setpinNumber(string s2)
	{
		pinNumber = s2;
	}
	void setid(string s3)
	{
		id = s3;
	}
	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, id, ',');
		getline(iss, cardNum, ',');
		getline(iss, pinNumber);
	}
	friend ostream& operator<<(ostream&, cards&);
};
void upgradeCards(cards*& Cdata, int CdataSize, cards obj)
{
	cards* ptr = new cards[CdataSize + 1];
	int i;
	for (i = 0; i < CdataSize; i++)
	{
		ptr[i] = Cdata[i];
	}
	ptr[i] = obj;
	delete[]Cdata;
	Cdata = ptr;
	ptr = nullptr;
	FinalCardSize++;
}
ostream& operator<<(ostream& fout, cards& obj)
{
	fout << obj.id << "," << obj.cardNum << "," << obj.pinNumber << endl;
	return fout;
}
class userClient :public users
{
protected:
	string userClientID;
	transactions data; // define composition(Has-a-Relationship) //
public:
	userClient()
	{
	}
	string getid()
	{
		return userClientID;
	}
	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, userClientID, ',');
		getline(iss, fullName, ',');
		getline(iss, address, ',');
		getline(iss, CNIC, ',');
		getline(iss, loginID, ',');
		getline(iss, password, ',');
		getline(iss, Balance);
	}
	// Function Implementations //
	void CreateAccount(userClient*& records, int recSize, cards*& Cdata, int CdataSize)
	{
		userClient temp;
		cout << "Enter the full name :";
		getline(cin, temp.fullName);
		cout << "Enter the address:";
		getline(cin, temp.address);
		cout << "Enter the CNIC :";
		getline(cin, temp.CNIC);
		cout << "Enter the login ID :";
		getline(cin, temp.loginID);
		cout << "Enter the Password :";
		getline(cin, temp.password);
		temp.Balance = "0";
		int val = recSize + 1;

		temp.userClientID = to_string(val);

		// now adding record in database //
		userClient* ptr = new userClient[recSize + 1];
		int i = 0;
		for (i; i < recSize; i++)
		{
			ptr[i] = records[i];
		}
		ptr[i] = temp;
		delete[]records;
		records = ptr;
		ptr = nullptr;
		// NOW ALLOCATING THE PIN AND CARD NUM .....
		FinalTotalAccReqs++;
		string code;
		cout << "enter 4 digit pin :";
		getline(cin, code);
		long long int value = (rand() % 7) * 1020400051001020 + (rand() % 100);
		string cardnumber = to_string(value);
		cards obj;
		obj.setid(temp.userClientID);
		obj.setCardnum(cardnumber);
		obj.setpinNumber(code);
		upgradeCards(Cdata, CdataSize, obj);
	}
	// Now transaction process working //
	void depositFund(userClient*& records, int recordSize, transactions*& transacData, int transacSize)
	{
		int cash = 0, id = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter password: ";
		getline(cin, pass);
		int val = 0;
		if (id > 0 && pass == records[id - 1].password)
		{
			cout << "Enter amount you want to deposit :";
			cin >> cash;
			val = cash;
			string temp = records[id - 1].Balance;
			cash += stoi(temp);
			temp = to_string(cash);
			records[id - 1].Balance = temp;
		}
		else {
			cout << "Invaid ID!!! or Password\n";
			exit(1);
		}
		data.setid(to_string(id));
		data.setTransacType("deposit");
		data.setDate(gettime());
		data.setamount(to_string(val));
		data.setReceiverID("");
		updateTransacData(transacData, transacSize, data);
	}
	void withdrawFund(userClient*& records, int recordSize, transactions*& transacData, int transacSize)
	{
		int cash = 0, id = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter password: ";
		getline(cin, pass);
		string temp;
		int val;
		if (id > 0 && pass == records[id - 1].password)
		{
			cout << "Enter amount you want to withdraw :";
			cin >> cash;
			val = cash;
			temp = records[id - 1].Balance;
			cash = stoi(temp) - cash;
			if (cash >= 0)
			{
				temp = to_string(cash);
				records[id - 1].Balance = temp;
			}
			else
				cout << "Not Enough Money.\n";

		}
		else {
			cout << "Invaid ID!!!\n";
			exit(1);
		}
		data.setid(to_string(id));
		data.setTransacType("withdraw");
		data.setDate(gettime());
		data.setamount(to_string(val));
		data.setReceiverID("");
		updateTransacData(transacData, transacSize, data);
	}
	void viewBalance(userClient* records)
	{
		int id = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter password: ";
		getline(cin, pass);
		if (id > 0)
			cout << "Your current Balance :" << records[id - 1].Balance << endl;
	}
	void viewTransactionHistory(userClient*& records, int recordSize, transactions*& transacData, int transacSize)
	{
		int id = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter password: ";
		getline(cin, pass);
		if (id > 0 && pass == records[id - 1].password)
		{
			cout << "Your transactions :\n";
			for (int i = 0; i < transacSize; i++)
			{
				if (transacData[i].getId() == id)
				{
					transacData[i].displayData();
				}
			}
		}
	}
	void transferFunds(userClient*& records, int recordSize, transactions*& transacData, int transacSize)
	{
		int id = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter password: ";
		getline(cin, pass);
		cout << "Enter Accout Id where you want to send Funds :";
		int id1 = 0;
		int amont;
		cin >> id1;
		if (id > 0 && pass == records[id - 1].password)
		{
			int cash;
			cout << "Enter amount you want to send :";
			cin >> cash;
			amont = cash;
			if (stoi(records[id - 1].Balance) >= cash)
			{
				string temp = records[id1 - 1].Balance;

				records[id - 1].Balance = to_string(stoi(records[id - 1].Balance) - cash);
				cash += stoi(temp);
				temp = to_string(cash);
				records[id1 - 1].Balance = temp;
			}
			data.setid(to_string(id));
			data.setTransacType("transfer");
			data.setDate(gettime());
			data.setamount(to_string(amont));
			data.setReceiverID(to_string(id1));
			updateTransacData(transacData, transacSize, data);
		}
		else {
			cout << "Invaid ID!!! or Password\n";
			exit(1);
		}
	}
	void UserAsUserClient(userClient*& records, int sizeRec, cards*& cardData, int cardSize, transactions*& transacData, int transacSize, userClient*& newAccs, int newAccsSize)
	{
		int choice = 0;
		cout << "Press 1 if you want to Create New Account: \n";
		cout << "Press 2 to login in your Account :\n";
		cin >> choice;
		cin.ignore();
		if (choice == 1)
		{
			CreateAccount(newAccs, newAccsSize, cardData, cardSize);
		}
		else if (choice == 2)
		{
			int id = 0;
			string pass = "";
			cout << "Enter your UserID:";
			cin >> id;
			cin.ignore();
			cout << "Enter password: ";
			getline(cin, pass);
			int val = 0;
			if (id > 0 && pass == records[id - 1].password)
			{
				system("cls");
				cout << "Press 1 to view your balance: \n"
					<< "Press 2 to view your transaction history :\n"
					<< "Press 3 to Deposit Funds : \n"
					<< "Press 4 to withdraw Funds: \n"
					<< "Press 5 to transfer funds: \n";

				cin >> choice;
				if (choice == 1)
				{
					viewBalance(records);
				}
				else if (choice == 2)
				{
					viewTransactionHistory(records, sizeRec, transacData, transacSize);
				}
				else if (choice == 3)
				{
					depositFund(records, sizeRec, transacData, transacSize);
				}
				else if (choice == 4)
				{
					withdrawFund(records, sizeRec, transacData, transacSize);
				}
				else if (choice == 5)
				{
					transferFunds(records, sizeRec, transacData, transacSize);
				}
				else { exit(1); }
			}
			else {
				cout << "Invaid Information!!!\n";
				exit(1);
			}

		}
	}
	friend ostream& operator<<(ostream&, userClient&);
};
ostream& operator<<(ostream& fout, userClient& obj)
{
	fout << obj.userClientID << "," << obj.fullName << "," << obj.address << "," << obj.CNIC << "," << obj.loginID << "," << obj.password
		<< "," << obj.Balance << endl;
	return fout;
}
//------------------------------------------- NOW Classes For Company Client-----------------------------//
bool checkCompanyperson(string id1, string id2)
{
	for (int i = 0; i < comp_empSize; i++)
	{
		if (comp_employees[i].userId == id1 && comp_employees[i].companyID == id2)
		{
			return true;
		}
	}
	return false;
}

class loans :public userClient
{
	string id;
	string amount;
public:
	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, id, ',');
		getline(iss, amount);
	}
	string getloanid()
	{
		return id;
	}
	string getMoney()
	{
		return amount;
	}
	void set(string id1, string temp)
	{
		id = id1;
		amount = temp;
	}
	friend ostream& operator<<(ostream&, loans&);
};
ostream& operator<<(ostream& fout, loans& obj)
{
	fout << obj.id << "," << obj.amount << endl;
	return fout;
}

class companyClient :public users
{
protected:
	cards cardObj;
	transactions data;
	string uniqueCompanyid;
	string companyTaxNum;
public:

	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, uniqueCompanyid, ',');
		getline(iss, fullName, ',');
		getline(iss, address, ',');
		getline(iss, companyTaxNum, ',');
		getline(iss, loginID, ',');
		getline(iss, password, ',');
		getline(iss, Balance);
	}
	string& getBalance()
	{
		return Balance;
	}
	string getid()
	{
		return uniqueCompanyid;
	}
	void CreateCompanyAccount(companyClient*& records, int companyDatasize, cards*& Cdata, int CdataSize)
	{
		companyClient temp;
		cout << "Enter the company name :";
		getline(cin, temp.fullName);
		cout << "Enter the address:";
		getline(cin, temp.address);
		cout << "Enter the Company tax number :";
		getline(cin, temp.companyTaxNum);
		cout << "Enter the login ID :";
		getline(cin, temp.loginID);
		cout << "Enter the Password :";
		getline(cin, temp.password);
		temp.Balance = "0";

		int val = stoi((records[companyDatasize - 1].uniqueCompanyid)) + 1;
		temp.uniqueCompanyid = to_string(val);
		// now adding record in database //
		companyClient* ptr = new companyClient[companyDatasize + 1];
		int i = 0;
		for (i; i < companyDatasize; i++)
		{
			ptr[i] = records[i];
		}
		ptr[i] = temp;
		delete[]records;
		records = ptr;
		ptr = nullptr;
		delete[]ptr;
		// NOW ALLOCATING THE PIN AND CARD NUM .....
		FinalCompanysize++;
		string code;
		cout << "enter 4 digit pin :";
		getline(cin, code);
		long long int value = (rand() % 7) * 1020400051001020 + (rand() % 100);
		string cardnumber = to_string(value);
		cards obj;
		obj.setid(temp.uniqueCompanyid);
		obj.setCardnum(cardnumber);
		obj.setpinNumber(code);
		upgradeCards(Cdata, CdataSize, obj);
	}

	void depositFund(companyClient*& companyData)
	{b
		int id = 0, idc = 0, cash = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter your CompanyID:";
		cin >> idc;
		cin.ignore();
		if (!checkCompanyperson(to_string(id), to_string(idc)))
		{
			cout << "You are not in company!!!\n";
			return;
		}
		idc = idc - 100;
		cout << "Enter password: ";
		getline(cin, pass);
		if (id > 0 && pass == companyData[idc - 1].password)
		{
			cout << "Enter amount you want to deposit :";
			cin >> cash;
			string temp = companyData[id - 1].Balance;
			cash += stoi(temp);
			temp = to_string(cash);
			companyData[idc - 1].Balance = temp;
		}
		else {
			cout << "Invaid ID!!! or Password\n";
			exit(1);
		}
	}
	void withdrawFund(companyClient*& companyData)
	{
		int id = 0, idc = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter your CompanyID:";
		cin >> idc;
		cin.ignore();
		if (!checkCompanyperson(to_string(id), to_string(idc)))
		{
			cout << "You are not in company!!!\n";
			return;
		}
		idc = idc - 100;
		cout << "Enter password: ";
		getline(cin, pass);
		int cash = 0;
		if (id > 0 && pass == companyData[idc - 1].password)
		{
			cout << "Enter amount you want to withdraw :";
			cin >> cash;
			string temp = companyData[idc - 1].Balance;
			cash = stoi(temp) - cash;
			if (cash >= 0)
			{
				temp = to_string(cash);
				companyData[idc - 1].Balance = temp;
			}
			else
				cout << "Not Enough Money.\n";

		}
		else {
			cout << "Invaid ID!!!\n";
			exit(1);
		}
	}
	void viewBalance(companyClient* companyData)
	{
		int id = 0, idc = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter your CompanyID:";
		cin >> idc;
		cin.ignore();
		if (!checkCompanyperson(to_string(id), to_string(idc)))
		{
			cout << "You are not in company!!!\n";
			return;
		}
		cin.ignore();
		idc = idc - 100;
		cout << "Enter password: ";
		getline(cin, pass);
		if (id > 0)
			cout << "Your current Balance :" << companyData[idc - 1].Balance << endl;
	}
	void requestLoan(companyClient*& companyData, loans*& loanReqs, int totalLoans)
	{
		int id = 0, idc = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter your CompanyID:";
		cin >> idc;
		cin.ignore();
		if (!checkCompanyperson(to_string(id), to_string(idc)))
		{
			cout << "You are not in company!!!\n";
			return;
		}
		idc = idc - 100;
		cout << "Enter password: ";
		getline(cin, pass);
		if (id > 0)
		{
			cout << "How much loan you want? ";
			int cash = 0;
			cin >> cash;
			loans obj;
			obj.set(to_string(idc + 100), to_string(cash));
			loans* ptr = new loans[totalLoans + 1];
			int i = 0;
			for (i; i < totalLoans; i++)
			{
				ptr[i] = loanReqs[i];
			}
			ptr[i] = obj;
			delete[] loanReqs;
			loanReqs = ptr;
			ptr = nullptr;
			FinaltotalLoans++;
		}
		cout << "Wait until approval!!!\n";

	}
	void viewTransactionHistory(companyClient*& companyData, int companyDataize, transactions*& transacData, int transacSize)
	{
		int id = 0, idc = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter your CompanyID:";
		cin >> idc;
		cin.ignore();
		if (!checkCompanyperson(to_string(id), to_string(idc)))
		{
			cout << "You are not in company!!!\n";
			return;
		}
		idc = idc - 100;
		cout << "Enter password: ";
		getline(cin, pass);
		if (id > 0 && pass == companyData[idc - 1].password)
		{
			cout << "Your transactions :\n";
			for (int i = 0; i < transacSize; i++)
			{
				if (transacData[i].getId() == id)
				{
					transacData[i].displayData();
				}
			}
		}
	}
	void transferFunds(companyClient*& companyData, int companyDataize, transactions*& transacData, int transacSize)
	{
		int id = 0, idc = 0;
		string pass = "";
		cout << "Enter your UserID:";
		cin >> id;
		cin.ignore();
		cout << "Enter your CompanyID:";
		cin >> idc;
		cin.ignore();
		if (!checkCompanyperson(to_string(id), to_string(idc)))
		{
			cout << "You are not in company!!!\n";
			return;
		}
		cout << "Enter password: ";
		getline(cin, pass);
		cout << "Enter Accout Id where you want to send Funds :";
		int id1 = 0;
		int amont;
		cin >> id1;
		idc = idc - 100;
		id1 = id1 - 100;
		if (id > 0 && pass == companyData[idc - 1].password)
		{
			int cash;
			cout << "Enter amount you want to send :";
			cin >> cash;
			amont = cash;
			if (stoi(companyData[idc - 1].Balance) >= cash)
			{
				string temp = companyData[id1 - 1].Balance;

				companyData[idc - 1].Balance = to_string(stoi(companyData[idc - 1].Balance) - cash);
				cash += stoi(temp);
				temp = to_string(cash);
				companyData[id1 - 1].Balance = temp;
			}
			data.setid(to_string(id));
			data.setTransacType("transfer");
			data.setDate(gettime());
			data.setamount(to_string(amont));
			data.setReceiverID(to_string(id1));
			updateTransacData(transacData, transacSize, data);
		}
		else
		{
			cout << "incorrect password!!!\n";
			exit(1);
		}
	}
	void UserAsCompanyClient(companyClient*& companyData, int companyDatasize, transactions*& transacData, int transacSize, loans*& loanReqs, int totalLoans, cards*& cardData, int cardDataSize)
	{
		int choice = 0;
		cout << "Press 1 to create new accounts :\n"
			<< "Press 2 to login in Company Accounts :\n";
		cin >> choice;
		system("cls");
		if (choice == 1)
		{
			cin.ignore();
			CreateCompanyAccount(companyData, companyDatasize, cardData, cardDataSize);
		}
		if (choice == 2)
		{
			int id = 0, idc = 0;
			string pass = "";
			cin.ignore();
			cout << "Enter your CompanyID:";
			cin >> idc;
			cin.ignore();
			idc = idc - 100;
			cout << "Enter password: ";
			getline(cin, pass);
			if (pass == companyData[idc - 1].password)
			{
				if (choice == 2)
				{
					system("cls");
					cout << "Press 1 to view balance :\n"
						<< "Press 2 to deposit funds :\n"
						<< "Press 3 to withdraw funds :\n"
						<< "Press 4 to transfer funds :\n"
						<< "Press 5 to view transaction history :\n";
					cin >> choice;
					if (choice == 1)
					{
						viewBalance(companyData);
					}
					else if (choice == 2)
					{
						depositFund(companyData);
					}
					else if (choice == 3)
					{
						withdrawFund(companyData);
					}
					else if (choice == 4)
					{
						transferFunds(companyData, companyDatasize, transacData, transacSize);
					}
					else if (choice == 5)
					{
						viewTransactionHistory(companyData, companyDatasize, transacData, transacSize);
					}
					else { exit(1); }
				}
				else
				{
					exit(1);
				}
			}
		}

	}

	friend ostream& operator<<(ostream&, companyClient&);
};
ostream& operator<<(ostream& fout, companyClient& obj)
{
	fout << obj.uniqueCompanyid << "," << obj.fullName << "," << obj.address << "," << obj.companyTaxNum << "," << obj.loginID << "," << obj.password
		<< "," << obj.Balance << endl;
	return fout;
}
//------------------------------------------------------------------------//
// 

// Now working for Bank Employee //

class BankEmployee : public users
{
protected:
	userClient Simpleuser;
	companyClient Companyuser;
	string employeeID;
public:
	void operator=(string temp)
	{
		istringstream iss(temp);
		getline(iss, employeeID, ',');
		getline(iss, loginID, ',');
		getline(iss, password);
	}
	bool operator==(BankEmployee& obj)
	{
		if (this->employeeID == obj.employeeID && this->password == obj.password && this->loginID == obj.loginID)
		{
			return true;
		}
		return false;
	}
	void verifyEmployee(BankEmployee*& array, int size, userClient*& userData, int userDataSize, transactions*& transacData, int transacSize, userClient*& userData1, int userDataSize1, loans*& loanArray, int loanNum, companyClient*& compArr, int compArrSize)
	{
		BankEmployee emp;
		cout << "Enter Your Employee ID: ";
		cin >> emp.employeeID;
		cout << "Enter Your UserID :";
		cin >> emp.loginID;
		cout << "Enter your Pass :";
		cin >> emp.password;
		int choice;
		cout << "----------------------------------------------------\n";
		if (array[stoi(emp.employeeID) - 1] == emp)
		{
			cout << "Press 1 to view list of all User Accounts :\n";
			cout << "Press 2 to view new Account Applications :\n";
			cout << "Press 3 to View Reject/Approve Loan request Section :\n";
			cout << "Press 4 to view transaction history of any account :\n";
			cout << "Press 5 to open Account Freeze/Close Section : \n";
			cin >> choice;
			if (choice == 1)
			{
				viewAccounts(userData, userDataSize);
			}
			else if (choice == 2)
			{
				approveAccountReqs(userData, userDataSize, userData1, userDataSize1);
			}
			else if (choice == 3)
			{
				approveLoanReqs(compArr, compArrSize, loanArray, loanNum);
			}
			else if (choice == 4)
			{
				viewTransactionHistory(transacData, transacSize);
			}
		}
	}
	void approveLoanReqs(companyClient*& companyData, int companyDataSize, loans*& loanArray, int loanNum)
	{
		int cash = 0;
		string id = "";
		system("cls");
		cout << "List Of un-approved loans :\n";
		for (int i = 0; i < loanNum; i++)
		{
			cout << loanArray[i] << endl;
		}
		cout << "----------------------------------------------------------\n";
		do {
			cout << "Enter id of account you want to approve loan and press -1 to exit :\n";
			cin >> id;
			if (stoi(id) != -1)
			{
				for (int i = 0; i < loanNum; i++)
				{
					if (id == loanArray[i].getloanid())
					{
						cash = stoi(loanArray[i].getMoney());
					}
				}
				// now adding record in database //
				for (int j = 0; j < companyDataSize; j++)
				{
					if (id == companyData[j].getid())
					{
						companyData[j].getBalance() = to_string(stoi(companyData[j].getBalance()) + cash);
						break;
					}
				}
				loans* ptr = new loans[loanNum - 1];
				for (int i = 0, k = 0; i < loanNum; i++)
				{
					if (id != loanArray[i].getloanid())
					{
						ptr[k++] = loanArray[i];
					}
				}
				delete[]loanArray;
				loanArray = ptr;
				ptr = nullptr;
				FinaltotalLoans--;
				loanNum--;
			}
			else { break; }

		} while (true);
	}
	void approveAccountReqs(userClient*& records, int recSize, userClient*& userData1, int userDataSize1)
	{
		int count = 0;
		string id = "";
		system("cls");
		cout << "List Of un-approved Accounts :\n";
		for (int i = 0; i < userDataSize1; i++)
		{
			cout << userData1[i] << endl;
		}
		cout << "----------------------------------------------------------\n";
		do {
			cout << "Enter id of account you want to approve and press -1 to exit :\n";
			cin >> id;
			if (stoi(id) != -1)
			{
				// now adding record in database //
				userClient* ptr = new userClient[recSize + 1];
				int i;
				for (i = 0; i < recSize; i++)
				{
					ptr[i] = records[i];
				}
				for (int j = 0; j < userDataSize1; j++)
				{
					if (id == userData1[j].getid())
					{
						ptr[i] = userData1[j];
						break;
					}
				}
				userClient* ptr2 = new userClient[userDataSize1 - 1];
				for (int i = 0, k = 0; i < userDataSize1; i++)
				{
					if (id != userData1[i].getid())
					{
						ptr2[k++] = userData1[i];
					}
				}
				delete[]userData1;
				userData1 = ptr2;
				ptr2 = nullptr;
				delete[]records;
				records = ptr;
				ptr = nullptr;
				FinalRecordSize++;
				FinalTotalAccReqs--;
				recSize++;
				userDataSize1--;
			}
			else { break; }

		} while (true);
	}
	void viewAccounts(userClient* userData, int userDataSize)
	{
		system("cls");
		cout << "---------------------------------------------\n";
		for (int i = 0; i < userDataSize; i++)
		{
			cout << userData[i] << endl;
		}
		cout << "---------------------------------------------\n";
	}
	void viewTransactionHistory(transactions* TransacData, int size)
	{
		system("cls");
		cout << "Enter ID num you want to check transactions of :";
		int id;
		cin >> id;
		cout << "------------------------------------------\n";
		for (int i = 0; i < size; i++)
		{
			if (TransacData[i].getId() == id)
			{
				cout << TransacData[i] << endl;
			}
		}
		cout << "------------------------------------------\n";
	}
};
//-------------------------------------------//

int main()
{
	userClient* records = nullptr;
	transactions* transactionData = nullptr;
	int sizeRec;
	fstream fin;
	fin.open("users.txt", ios::in);
	sizeRec = 0;
	string temp;
	fin >> sizeRec;
	getline(fin, temp);
	records = new userClient[sizeRec];
	for (int i = 0; i < sizeRec; i++)
	{
		getline(fin, temp);
		records[i] = temp;
	}
	fin.close();

	int totalAccReq = 0;
	fin.open("NewAccountRequests.txt", ios::in);
	totalAccReq = 0;
	fin >> totalAccReq;
	getline(fin, temp);
	userClient* totalnewAcc = new userClient[totalAccReq];
	for (int i = 0; i < totalAccReq; i++)
	{
		getline(fin, temp);
		totalnewAcc[i] = temp;
	}
	fin.close();
	fin.open("admin.txt", ios::in);
	int sizeBankEmp = 0;
	fin >> sizeBankEmp;
	getline(fin, temp);
	BankEmployee* employees = new BankEmployee[sizeBankEmp];
	for (int i = 0; i < sizeBankEmp; i++)
	{
		getline(fin, temp);
		employees[i] = temp;
	}
	fin.close();

	fin.open("cards.txt", ios::in);
	int sizeCardData;
	fin >> sizeCardData;
	cards* cardData = new cards[sizeCardData];
	getline(fin, temp);
	for (int i = 0; i < sizeCardData; i++)
	{
		getline(fin, temp);
		cardData[i] = temp;
	}
	fin.close();
	fin.open("transactions.txt", ios::in);
	int transacDataSize;
	fin >> transacDataSize;
	transactionData = new transactions[transacDataSize];
	getline(fin, temp);
	for (int i = 0; i < transacDataSize; i++)
	{
		getline(fin, temp);
		transactionData[i] = temp;
	}
	fin.close();

	fin.open("companies.txt", ios::in);
	int companyDatasize = 0;

	fin >> companyDatasize;
	companyClient* companyData = new companyClient[companyDatasize];
	getline(fin, temp);
	for (int i = 0; i < companyDatasize; i++)
	{
		getline(fin, temp);
		companyData[i] = temp;
	}
	fin.close();
	fin.open("companies_employees.txt", ios::in);
	int comp_employ_Size = 0;
	fin >> comp_employ_Size;
	comp_empSize = comp_employ_Size;
	comp_employees = new company_employee[comp_employ_Size];
	getline(fin, temp);
	for (int i = 0; i < comp_employ_Size; i++)
	{
		getline(fin, temp);
		comp_employees[i] = temp;
	}
	fin.close();
	fin.open("LoanRequests.txt", ios::in);
	int loanreqnum = 0;
	fin >> loanreqnum;
	loans* loansArray = new loans[loanreqnum];
	getline(fin, temp);
	for (int i = 0; i < loanreqnum; i++)
	{
		getline(fin, temp);
		loansArray[i] = temp;
	}
	fin.close();
	int choice = 0;
	cout << "Press 1 if you want to use application as User Client :\n"
		<< "Press 2 if you want to use application as Company Client :\n"
		<< "Press 3 if you want to use application as Bank Employee :\n";
	cin >> choice;
	cin.ignore();
	if (choice == 1)
	{
		system("cls");
		records[0].UserAsUserClient(records, sizeRec, cardData, sizeCardData, transactionData, transacDataSize, totalnewAcc, totalAccReq);
	}
	else if (choice == 2)
	{
		system("cls");
		companyData[0].UserAsCompanyClient(companyData, companyDatasize, transactionData, transacDataSize, loansArray, loanreqnum, cardData, sizeCardData);
	}
	else if (choice == 3)
	{
		system("cls");
		employees[0].verifyEmployee(employees, sizeBankEmp, records, sizeRec, transactionData, transacDataSize, totalnewAcc, totalAccReq, loansArray, loanreqnum, companyData, companyDatasize);
	}
	else
	{
		exit(1);
	}
	//employees[0].verifyEmployee(employees, sizeBankEmp, records, sizeRec, transactionData, transacDataSize,totalnewAcc,totalAccReq,loansArray,loanreqnum,companyData,companyDatasize);
	//records[0].UserAsUserClient(records, sizeRec, cardData, sizeCardData, transactionData, transacDataSize, totalnewAcc, totalAccReq);
	//companyData[0].transferFunds(companyData, companyDatasize, transactionData, transacDataSize);
	//companyData[0].depositFund(companyData);
	//companyData[0].CreateCompanyAccount(companyData, companyDatasize, cardData, sizeCardData);
	//records[0].CreateAccount(totalnewAcc,totalAccReq, cardData, sizeCardData);
	//companyData[0].requestLoan(companyData, loansArray, loanreqnum);
	//employees[0].approveLoanReqs(companyData, companyDatasize, loansArray, loanreqnum);
	// now wrting data back to files //
	fstream fout;
	fout.open("users.txt", ios::out);
	FinalRecordSize += sizeRec;
	fout << FinalRecordSize << endl;
	for (int i = 0; i < FinalRecordSize; i++)
	{
		fout << records[i];
	}
	fout.close();
	fout.open("transactions.txt", ios::out);
	FinaltrasacSize += transacDataSize;
	fout << FinaltrasacSize << endl;
	for (int i = 0; i < FinaltrasacSize; i++)
	{
		fout << transactionData[i];
	}
	fout.close();
	fout.open("cards.txt", ios::out);
	FinalCardSize += sizeCardData;
	fout << FinalCardSize << endl;
	for (int i = 0; i < FinalCardSize; i++)
	{
		fout << cardData[i];
	}
	fout.close();
	fout.open("companies.txt", ios::out);
	FinalCompanysize += companyDatasize;
	fout << FinalCompanysize << endl;
	for (int i = 0; i < FinalCompanysize; i++)
	{
		fout << companyData[i];
	}
	fout.close();
	fout.open("NewAccountRequests.txt", ios::out);
	FinalTotalAccReqs += totalAccReq;
	fout << FinalTotalAccReqs << endl;
	for (int i = 0; i < FinalTotalAccReqs; i++)
	{
		fout << totalnewAcc[i];
	}
	fout.close();
	fout.open("LoanRequests.txt", ios::out);
	FinaltotalLoans += loanreqnum;
	fout << FinaltotalLoans << endl;
	for (int i = 0; i < FinaltotalLoans; i++)
	{
		fout << loansArray[i];
	}
	fout.close();
	delete[] records;
	delete[] transactionData;
	delete[] cardData;
	delete[] companyData;
	delete[] employees;
	system("pause");
	return 0;
}
