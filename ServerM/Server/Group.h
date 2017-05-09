#pragma once
#include<string>
#include<iostream>
#include<deque>
#include"Account.h"
using namespace std;
class Group
{
private:
	string GroupName;
	int OwnerID;
	deque<Account*> MemberList;

public:
	Group(int ID,string name);
	string GetGroupName() { return this->GroupName; };
	string SetGroupName();
	int GetOwnerId() { return this->OwnerID; };
	void addAccount(Account* a) { MemberList.push_back(a); };
	void SeeMembers();



};
