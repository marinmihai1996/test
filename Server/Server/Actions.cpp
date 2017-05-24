#ifndef _header_4344
#define _header_4334

#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
#include"LogGroups.h"
#include"Utils.h"
#include "Admin.h"
#include "Owner.h"
#include "Member.h"
using namespace std;
ofstream write;

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

void Server::RewriteAccountFile()
{
	Memory& mem = Memory::GetInstance();
	for (int i = 0; i < mem.GetAccountListSize(); i++) {
		this->SaveAccount(mem.getAccountForIndex(i));
	}
}

void  Server::SaveAccount(Account *a){

	LogAccounts&MyLogAccounts = LogAccounts::GetInstance();
	string aux;
	aux.append(a->GetUsername());
	aux.append(" ");
	aux.append(a->GetPassword());
	aux.append(" ");
	aux.append(std::to_string(a->GetId()));
	aux.append("\n");
	MyLogAccounts.Write(aux);
	
}

void Server::SeeMemberList(std::string message)
{
	Memory& mem = Memory::GetInstance();
	vector<string> MemberList;
	vector<string> tokens = split(message, '.'); // put the strings in a vector -> delimitator='.'
	string groupName = tokens.at(1);
	int ID = stoi(tokens.at(2));
	
	MemberList = mem.GetMemberList(groupName);
	string Message = "members";
	for (int i = 0; i < MemberList.size(); i++) {
		Message.append(".");
		Message.append(MemberList.at(i));
	}
	SendString(ID, Message);	
}
void Server::SeeAdminList(std::string message)
{
	Memory& mem = Memory::GetInstance();
	vector<string> AdminList;
	vector<string> tokens = split(message, '.'); // put the strings in a vector -> delimitator='.'
	string groupName = tokens.at(1);
	int ID = stoi(tokens.at(2));

	AdminList = mem.GetAdminList(groupName);
	string Message = "admins";
	for (int i = 0; i < AdminList.size(); i++) {
		Message.append(".");
		Message.append(AdminList.at(i));
	}
	SendString(ID, Message);
}
void Server::SeeGroupList(std::string message) {
	Memory& mem = Memory::GetInstance();
	vector<string> GroupList;
	vector<string> tokens = split(message, '.');
	int ID = stoi(tokens.at(1));
	Account*a = mem.getAccount(ID);
	GroupList = mem.GetGroupList(a);
	string Message = "groupList";
	for (int i = 0; i < GroupList.size(); i++) {
		Message.append(".");
		Message.append(GroupList[i]);
	}
	SendString(ID, Message);

}

//void Server::ViewAccountsList()
//{
//	//std::cout << " The Accounts are: " << std::endl;
//	Memory& mem = Memory::GetInstance();
//	mem.ViewAccountsList();
//}
#endif