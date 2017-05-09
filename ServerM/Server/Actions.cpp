#ifndef _header_4344
#define _header_4334
#include<vector>
#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
#include<fstream>
using namespace std;
ofstream write;
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

int Server::GetIdClient(std::string name)
{
	Memory& mem = Memory::GetInstance();
	return mem.GetId(name);
}

void Server::CreateGroup(int ID,std::string Message){ 
	std::string groupName = Message.substr(11, std::string::npos);
	Group* NewGroup = new Group(ID, groupName);
	Memory& mem = Memory::GetInstance();
	NewGroup->addAccount(getAccount(ID));
	groupName.append(".txt");
   // FILE *f = fopen(groupName.c_str(),"a+");
	vector<string> tokens = split(groupName, '.');
	string name = tokens.at(0);
	ofstream OutPut;
	Account*aux = getAccount(ID);

	OutPut.open(groupName, ofstream::binary);
	OutPut << aux->GetUsername();

	OutPut << " ";
	OutPut << ID;

	//fprintf(f,"%s ",name.c_str()); 
	
	//fprintf(f," %d\n",ID);
	
	mem.AddInGroupList(NewGroup);
}


void Server::SingUp(std::string message) {
	std::string accountNameAndPass = message.substr(13, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password= tokens.at(1);
	int ID = std::stoi(tokens.at(2)); 
	Memory& mem = Memory::GetInstance();

	if (mem.VerifyExistanceAccount(username, password) == 0)
	{
		ID = mem.VerifyID(ID);
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


void Server::InviteClient(string message)
{
	std::string IDandGroupName = message.substr(12, std::string::npos);
	vector<string> tokens = split(IDandGroupName, '.'); // put the strings in a vector -> delimitator='.'
	string clientName = tokens.at(0);
	int ID = this->GetIdClient(clientName);
	string GroupName = tokens.at(1);
	for (int i = 0; i < IDs; i++)
	{
		if (i == ID) //If connection is the user who sent the message...
		if (!SendString(i,GroupName)) //Send message to connection at index i, if message fails to be sent...
		{
			std::cout << "Failed to send message from server to client ID: " << i << std::endl;

		}
	}
	  

}

#endif