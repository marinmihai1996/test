#ifndef _header_4344
#define _header_4334
#include<vector>
#include<direct.h>
#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
#include"LogGroups.h"
#include<fstream>
using namespace std;
ofstream write;

void CreateDirectory(string name)
{
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(name);
	_mkdir(path.c_str());
}

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
	Memory&mem = Memory::GetInstance();
	string ownerName = mem.getAccount(ID)->GetUsername();
	if (mem.ExistsGroup(groupName) == false)
	{
		Group* NewGroup = new Group(groupName, ownerName);
		LogGroups&groups = LogGroups::GetInstance();
		string auxx;
		auxx.append(groupName);
		auxx.append(" ");
		auxx.append(ownerName);
		auxx.append("\n");
		groups.Write(auxx);

		NewGroup->addAccount(getAccount(ID)); // il adaug in memorie
		groupName.append(".txt"); // ii creez fisierul
		vector<string> tokens = split(groupName, '.');
		string name = tokens.at(0);
		ofstream OutPut;
		Account*aux = getAccount(ID); // scriu in fisier owner-ul
		OutPut.open(groupName, ofstream::binary);
		OutPut << aux->GetUsername();
		mem.AddInGroupList(NewGroup);
		string message = "groupCreated.";
		message.append(groupName);
		SendString(ID, message);
	}
	else {
		string message = "This name is taken.Choose another one";
		SendString(ID, message);
	}
}
void Server::RewriteAccountFile()
{
	Memory& mem = Memory::GetInstance();
	for (int i = 0; i < mem.GetAccountListSize(); i++) {
		this->SaveAccount(mem.getAccountForIndex(i));
	}
}

void Server::SingUp(std::string message) {
	std::string accountNameAndPass = message.substr(13, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password= tokens.at(1);
	int ID = std::stoi(tokens.at(2)); 
	Memory& mem = Memory::GetInstance();

	if (mem.VerifyExistanceAccount(username, password,ID) == 0)
	{
	    mem.ChangeIdForSingUp(ID);
		mem.CleanAccountFile();//sterg continutul fisirului
		Account *newAccount = new Account(username, password,ID);
		mem.AddInAccountList(newAccount);
		this->RewriteAccountFile();// rescriu fisierul Accounts.txt
		CreateDirectory(username);
		
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string ToSend = "Your account is created!\n";
		SendString(ID, ToSend);
		
	}
	else if (mem.VerifyExistanceAccount(username, password,ID) == 1)
	{
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message = "This account already exists. Please Login!\n";
		SendString(ID,message);
	}
	else {
	
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message = "This username is taken.Please choose another one!\n";
		SendString(ID, message);
	}
}
void Server::LogIn(std::string message) {
	
	std::string accountNameAndPass = message.substr(6, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password = tokens.at(1);
	int ID = stoi(tokens.at(2));
	
	Memory& mem = Memory::GetInstance();
	if (mem.VerifyExistanceAccount(username, password,ID) == 1) {
		// este in memorie
		mem.ChangeIdForLogIn(ID,username); // le schimb in memorie
		mem.CleanAccountFile();
		this->RewriteAccountFile();

		string IdMessage = "ID.";

		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message= "You are now online!\n";
		mem.GoOnline(ID);
		this->SendString(ID, message);
	}
	else {
		//nu e in memorie
		string message = "You don't have an account!Please Sing up!\n";
		this->SendString(ID, message);
	}
}


void  Server::SaveAccount(Account *a){

	LogClass&MyLogClass = LogClass::GetInstance();
	string aux;
	aux.append(a->GetUsername());
	aux.append(" ");
	aux.append(a->GetPassword());
	aux.append(" ");
	aux.append(std::to_string(a->GetId()));
	aux.append("\n");
	MyLogClass.Write(aux);
	
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



void Server::GroupChat(std::string Message)
{
	std::string MessageAndID = Message.substr(6, std::string::npos);
	vector<string> tokens = split(MessageAndID,'.'); // put the strings in a vector -> delimitator='.'
	int ID = std::stoi(tokens.at(0));
	string message = tokens.at(1);

	for (int i = 0; i < IDs; i++)
	{
		if (i == ID) //If connection is the user who sent the message...
			continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
		if (!SendString(i, message)) //Send message to connection at index i, if message fails to be sent...
		{
			std::cout << "Failed to send message from client ID: " << ID << " to client ID: " << i << std::endl;
		}
	}
}

void Server::ConnectToGroup(std::string Message) {
	
	std::string groupNameAndID = Message.substr(7, std::string::npos);
	Memory& mem = Memory::GetInstance();
	vector<string> tokens = split(groupNameAndID,'.');
	string groupName = tokens.at(0);
	int userID = stoi(tokens.at(1));
	Account*user = mem.getAccount(userID);
	//verific daca grupul exista
	if (mem.ExistsGroup(groupName) == true) {
		Group *group = mem.getGroup(groupName);
		//acum verific daca user-ul face parte din grup
		if (group->ExistMember(user) == true) {
			string message = "InGroup.";
			message.append(groupName);
			SendString(userID, message);
		}
		else {
			string message = "You are not a member of this group!";
			SendString(userID, message);
		}
	}
	else {
		string message = "This group do not exists!";
		SendString(userID, message);
	}

}

void Server::deleteGroup(std::string Message)
 {
	std::string MessageAndID = Message.substr(6, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	
		int ID = std::stoi(tokens.at(0));
	string message = tokens.at(1);
	Memory&mem = Memory::GetInstance();
	if (mem.getAccount(ID)->deleteGroup())
	 {
		mem.deleteGroup(mem.getGroupNr(message));
		message.append(".txt");
		char * writable = new char[message.size() + 1];
		std::copy(message.begin(), message.end(), writable);
		writable[message.size()] = '\0'; // don't forget the terminatination
		remove(writable);
		delete[] writable;
		}
	
}

void Server:: kickMember(std::string Message)
 {
	std::string MessageAndID = Message.substr(6, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	
		int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	string numeMembru = tokens.at(2);
	Memory&mem = Memory::GetInstance();
	
		if (mem.getAccount(ID)->kickMember())
		 mem.getGroup(numeGrup)->kickMember(numeMembru);
		
	
}

#endif