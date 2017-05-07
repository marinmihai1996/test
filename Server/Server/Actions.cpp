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

void Server::CreateGroup(int ID,std::string Message){
	std::string groupName = Message.substr(11, std::string::npos);
	Group* NewGroup = new Group(ID, groupName);
	Memory& mem = Memory::GetInstance();
	mem.AddInGroupList(NewGroup);
	
	
}


void Server::CreateAccount(std::string message) {
	std::string accountNameAndPass = message.substr(13, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password= tokens.at(1);
	Memory& mem = Memory::GetInstance();
	if (mem.VerifyExistanceAccount(username, password) == true)
	{
		Account *newAccount = new Account(username, password);
		mem.AddInAccountList(newAccount);
		this->SaveAccount(*newAccount);
	}
}


void  Server::SaveAccount(Account a){
	LogClass&MyLogClass = LogClass::GetInstance();
	MyLogClass.Write(a.GetUsername());
	MyLogClass.Write(" ");
	MyLogClass.Write(a.GetPassword());
	MyLogClass.Write("\n");
}


void Server::RestoreMemory()
{
	Memory& mem = Memory::GetInstance();
	mem.RestoreAccountList();
	mem.RestoreGroupsList();
}


#endif