#pragma once
#include<string>
#include<iostream>
#include<deque>
#include"Account.h"
#include"Admin.h"
#include<vector>
using namespace std;
class Account;
class Group
{
private:
	string groupName;
	string ownerName;
	deque<Account*> MemberList;
	vector<Account*>AdminList;

public:
	Group(string groupName, string ownerName);
	string GetGroupName() { return this->groupName; };
	string GetGroupOwnerName() { return this->ownerName; };
	void addAccount(Account* a) { MemberList.push_back(a); }

	void addAdmin(Account* a) { AdminList.push_back(a); };
	void SeeMembers();
	vector<string> GetMemberList();
	void kickMember(std::string name);
	bool ExistMember(Account*);
	

};
