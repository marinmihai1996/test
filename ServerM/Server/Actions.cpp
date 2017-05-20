#ifndef _header_4344
#define _header_4334
#include<vector>
#include<direct.h>
#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
#include"LogGroups.h"
#include<fstream>
#include "Admin.h"
#include "Owner.h"
#include "Member.h"
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
		OutPut.open(groupName, std::ofstream::out | std::ofstream::app);
		OutPut << aux->GetUsername();
		OutPut << "\n";
		OutPut.close();
	
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
	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(message, '.'); // put the strings in a vector -> delimitator='.'
	int ID = stoi(tokens.at(1));
	string clientName = tokens.at(2);
	if (mem.getAccount(ID)->Rights->InviteClient())
	{
	Account *account = mem.getAccount(clientName);

	
		int ID = account->GetId();
		string GroupName = tokens.at(2);

		string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
		path.append(clientName.c_str());
		path.append("/");
		path.append("invitations.txt");

		std::ofstream ofs;
		ofs.open(path, std::ofstream::out | std::ofstream::app);

		ofs << GroupName;
		ofs << "\n";
		ofs.close();
	}
}



void Server::AddMemberInGroup(string message)
{
	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(message, '.');
	string group = tokens.at(1);
	int userID = stoi(tokens.at(2));
	Group*Group = mem.getGroup(group);
	Account *account = mem.getAccount(userID);
	Group->addAccount(account);
	ofstream OutPut;
	group.append(".txt");
	OutPut.open(group, std::ofstream::out | std::ofstream::app); 
	OutPut << account->GetUsername();
	OutPut << "\n";
	OutPut.close();

}

void Server::SeeInvitations(string message)
{
	vector<string> tokens = split(message, '.');
	int UserId = stoi(tokens.at(1));
	Memory&mem = Memory::GetInstance();
	Account*acc = mem.getAccount(UserId);
	string username = acc->GetUsername();
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(username);
	path.append("/invitations.txt");
	SendString(UserId, path);
}


void Server::GroupChat(std::string Message)
{
	Memory&mem = Memory::GetInstance();
	std::string MessageAndID = Message.substr(6, std::string::npos);
	vector<string> tokens = split(MessageAndID,'.'); // put the strings in a vector -> delimitator='.'
	string groupName = tokens.at(0);
	int ID = std::stoi(tokens.at(1));
	string message = tokens.at(2);
	Group*group = mem.getGroup(groupName);
	vector<string> GroupMemberList = mem.GetMemberList(group);
	int IdVector[15];
	string SenderName;
	
	for (int i = 0; i < GroupMemberList.size(); i++)
	{
		Account *a = mem.getAccount(GroupMemberList.at(i));
		IdVector[i] = a->GetId();
		if (IdVector[i] == ID) SenderName = a->GetUsername();
	}
	
	for (int i = 0; i < GroupMemberList.size(); i++)
	{
		if (IdVector[i] == ID) //If connection is the user who sent the message...
			continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
		string Mes = "chatg.";
		Mes.append(groupName);
		Mes.append(".");
		Mes.append(SenderName);
		Mes.append(".");
		Mes.append(GroupMemberList.at(i));
		Mes.append(".");
		Mes.append(message);
		
		if (!SendString(IdVector[i], Mes)) //Send message to connection at index i, if message fails to be sent...
		{
			string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
			path.append(GroupMemberList.at(i));
			path.append("/");
			path.append(groupName);
			path.append(".txt");
			ofstream OutPut;
			OutPut.open(path, std::ofstream::out | std::ofstream::app);
			OutPut << SenderName;
			OutPut << ":";
			OutPut << message;
			OutPut << "\n";
			OutPut.close();
			std::cout << "The user " << i << "is offline. Gonna see the messages when logs in" << std::endl;
			//std::cout << "Failed to send message from client ID: " << ID << " to client ID: " << i << std::endl;
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

	std::ifstream file;
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(groupName);
	path.append(".txt");

	file.open(path, std::ifstream::in);
	string OwnerName;
	std::getline(file, OwnerName);

	if (OwnerName.compare(user->GetUsername()) == 0)
		user->Rights = new Owner;
	else
		user->Rights = new Member;
	
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
	//Message= deletgroup.id.numegrup.
	std::string MessageAndID = Message.substr(10, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	
		int ID = std::stoi(tokens.at(0));
	string message = tokens.at(1);
	Memory&mem = Memory::GetInstance();
	if (mem.getAccount(ID)->Rights->deleteGroup())
	 {
		mem.deleteGroup(mem.getGroupNr(message));
		message.append(".txt");
		
		char * writable = new char[message.size() + 1];
		std::copy(message.begin(), message.end(), writable);
		writable[message.size()] = '\0'; // don't forget the terminatination
		remove(writable);
		delete[] writable;
		//sa sterg si din Groups.txt
		}
	else
	{
		string message = "You don't have the rights to do this";
		SendString(ID, message);
	}
	
}

void Server:: kickMember(std::string Message)
 {
	//Message= kickmember.id.numegrup.numemembrupentrukick
	std::string MessageAndID = Message.substr(10, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
		int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	string numeMembru = tokens.at(2);
	Memory&mem = Memory::GetInstance();	
		if (mem.getAccount(ID)->Rights->kickMember())
		 mem.getGroup(numeGrup)->kickMember(numeMembru);
		else
		{
			string message = "You don't have the rights to do this";
			SendString(ID, message);
		}
}


void Server::MakeAdmin(std::string Message)
{
	///makeadmin.id.numegrup.numemembru

	std::string MessageAndID = Message.substr(9, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	string numeMembru = tokens.at(2);

	Memory&mem = Memory::GetInstance();
	if (mem.getAccount(ID)->Rights->DowngradeAdmin())
	{
		if (mem.getGroup(numeGrup)->ExistMember(mem.getAccount(numeMembru)))
		{
			if (mem.getAccount(numeMembru)->Rights->getstatut() == "admin")
			{
				free(mem.getAccount(ID)->Rights);
				mem.getAccount(numeMembru)->Rights = new Admin;

			}
			else
			{
				string message = "This member is allready administrator";
				SendString(ID, message);
			}
		}
		else
		{
			string message = "The accout is not a member  of this group";
			SendString(ID, message);
		}
	}
	else
	{
		string message = "You don't have the rights to do this";
		SendString(ID, message);
	}

}

void Server::DowngradeAdmin(std::string Message)
{
	///downgradeadmin.id.numegrup.numeadmin

	std::string MessageAndID = Message.substr(14, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	string numeMembru = tokens.at(2);
	Memory&mem = Memory::GetInstance();
	if (mem.getAccount(ID)->Rights->DowngradeAdmin())
	{
		if (mem.getGroup(numeGrup)->ExistMember(mem.getAccount(numeMembru)))
		{
			if (mem.getAccount(numeMembru)->Rights->getstatut() == "admin")
			{
				Memory&mem = Memory::GetInstance();
				free(mem.getAccount(ID)->Rights);
				mem.getAccount(numeMembru)->Rights = new Member;
			}
			else
			{
				string message = "This member is not an administrator";
				SendString(ID, message);
			}
		}
		else
		{
			string message = "The accout is not a member  of this group";
			SendString(ID, message);
		}
	}
	else
	{
		string message = "You don't have the rights to do this";
		SendString(ID, message);
	}
}
	

void Server::ViewAccountsList()
{
	std::cout << " The Accounts are: " << std::endl;
	Memory& mem = Memory::GetInstance();
	mem.ViewAccountsList();
}
#endif