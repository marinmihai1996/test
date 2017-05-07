#pragma once
#include<iostream>
#include"Group.h"
#include"Account.h"
#include<deque>
#include"LogAccounts.h"

using namespace std;


class Memory
{
private:
	Memory();
	static Memory *mpInstance;
	~Memory();
	deque <Group*> GroupList;
	deque <Account*> AccountList;

public:
	static Memory& GetInstance();
	void ViewGroupsList();
	void ViewAccountsList();
	void AddInGroupList(Group*);
	void AddInAccountList(Account*);
	void RestoreAccountList();
	void RestoreGroupsList();
	bool VerifyExistanceAccount(string,string);

};