#pragma once
#include<string>
#include<iostream>
#include<deque>
#include"Account.h"
#include"Admin.h"
#include<vector>
#include"ServerMemory.h"
using namespace std;
class Account;
class Group
{
private:
	string groupName;
	string ownerName;
	deque<Account*> MemberList;
	deque<Account*>AdminList;

public:
	Group(string groupName, string ownerName);
	string GetGroupName() { return this->groupName; };
	string GetGroupOwnerName() { return this->ownerName; };
	void addAccount(Account* a) { MemberList.push_back(a); }

	void addAdmin(Account* a) { AdminList.push_back(a); };
	vector<string> GetMemberList();
	vector<string> GetAdminList();
    bool kickMember(std::string name);
	bool kickAdmin(std::string name);
	bool ExistMember(Account*);
	bool ExistAdmin(Account*);
	Account* getAccount(string accountName);
	

};
