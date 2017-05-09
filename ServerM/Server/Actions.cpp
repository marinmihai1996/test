#ifndef _header_4344
#define _header_4334
#include<vector>
#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
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
Account* Server::getAccount(int ID)
{
	Memory& mem = Memory::GetInstance();
	return mem.getAccount(ID);
}



void Server::CreateGroup(int ID,std::string Message){ //aici e ceva nou
	std::string groupName = Message.substr(11, std::string::npos);
	Group* NewGroup = new Group(ID, groupName);
	Memory& mem = Memory::GetInstance();
	NewGroup->addAccount(getAccount(ID));
	groupName.append(".txt");
	FILE *f = fopen(groupName.c_str(),"a+");
	vector<string> tokens = split(groupName, '.');
	string name = tokens.at(0);
	fprintf(f,"%s\n",name);
	fprintf(f,"%d\n",ID);
	fclose(f);
	mem.AddInGroupList(NewGroup);
}


void Server::CreateAccount(std::string message) {
	std::string accountNameAndPass = message.substr(13, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password= tokens.at(1);
	int ID = std::stoi(tokens.at(2)); 
	Memory& mem = Memory::GetInstance();
	ID = mem.VerifyID(ID);
	if (mem.VerifyExistanceAccount(username, password) == 0)
	{
		Account *newAccount = new Account(username, password,ID);
		mem.AddInAccountList(newAccount);
		this->SaveAccount(*newAccount);
		int AccountCreated = 1000;
		SendInt(ID, AccountCreated);

	}
	else if (mem.VerifyExistanceAccount(username, password) == 1)
	{
		///string message = "This account already exists. Please Login!\n";
		int Accountexists = 1001;
		SendInt(ID, Accountexists);
	}
	else {
		//string message = "This username is taken.Please choose another one!\n";
		int SameUsername = 1002;
		SendInt(ID, SameUsername);
	}
}
void Server::LogIn(std::string message) {
	std::string accountNameAndPass = message.substr(6, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password = tokens.at(1);
	int ID = std::stoi(tokens.at(2));
	Memory& mem = Memory::GetInstance();
	if (mem.VerifyExistanceAccount(username, password) == 1) {
		// este in memorie
		mem.GoOnline(ID);
		int messageCode = 1003;
		this->SendInt(ID, messageCode);
	}
	else {
		//nu e in memorie
		int messageCode = 1004;
		this->SendInt(ID, messageCode);
	}
}






void  Server::SaveAccount(Account a){
	LogClass&MyLogClass = LogClass::GetInstance();
	MyLogClass.Write(a.GetUsername());
	MyLogClass.Write(" ");
	MyLogClass.Write(a.GetPassword());
	MyLogClass.Write(" ");
	MyLogClass.Write(std::to_string(a.GetId()));
	MyLogClass.write('\n');
}


void Server::RestoreMemory()
{
	Memory& mem = Memory::GetInstance();
	mem.RestoreAccountList();
	mem.RestoreGroupsList(); //de facut asta
}


#endif