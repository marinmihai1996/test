#include<iostream>
#include"ServerMemory.h"
#include <fstream>
#include<vector>


static vector<string> split(const string &text, char sep) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}


Memory* Memory::mpInstance = NULL;
Memory::Memory()
{

}
Memory&Memory::GetInstance()
{
	if (mpInstance == NULL)
	{
		mpInstance = new Memory();
	}
	return *mpInstance;
}

void Memory::ViewGroupsList()
{
	for (int i = 0; i < GroupList.size(); i++)
	{
		std::cout << GroupList[i]->GetGroupName() << std::endl;
	}
}

void Memory::ViewAccountsList()
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		std::cout <<AccountList[i]->GetUsername() << std::endl;
	}
}


void Memory::AddInAccountList(Account*a){

	AccountList.push_back(a);
}

void Memory::AddInGroupList(Group*a){

	GroupList.push_back(a);
}
void Memory::RestoreAccountList() {
	LogClass& Log = LogClass::GetInstance();
	string line;
	ifstream myfile("Accounts.txt");
	if (myfile.good()){
		while (getline(myfile, line)){  // same as: while (getline( myfile, line ).good())
			
			vector<string>tokens = split(line, ' ');
			string username = tokens.at(0);
			string password = tokens.at(1);
			Account *newAccount = new Account(username, password);
			this->AddInAccountList(newAccount);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
};
void Memory::RestoreGroupsList() {
};


bool Memory::VerifyExistanceAccount(string usename, string pass)  // astea trebuie sa le trimit inapoi la client
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		if (AccountList[i]->GetUsername().compare(usename) != string::npos){

			if (AccountList[i]->GetPassword().compare(pass) != string::npos){
				std::cout << "Account already existing! Please Log In!" << std::endl;
				return false;
			}
			else {
				std::cout << "This username is taken. Please choose another one!" << std::endl;
				return false;
			}
		}
	}
	return true;
}