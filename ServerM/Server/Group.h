#pragma once
#include<string>
#include<iostream>
#include<deque>
#include"Account.h"
using namespace std;
class Group
{
private:
	string groupName;
	string ownerName;
	deque<Account*> MemberList;

public:
	Group(string groupName, string ownerName);
	string GetGroupName() { return this->groupName; };
	string SetGroupName();
	string GetGroupOwnerName() { return this->ownerName; };
	void addAccount(Account* a) { MemberList.push_back(a); };
	void SeeMembers();



};
