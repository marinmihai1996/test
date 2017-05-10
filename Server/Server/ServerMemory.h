#pragma once
#include<iostream>
#include"Group.h"
#include"Account.h"
#include<deque>
#include"LogAccounts.h"
#include"Server.h"
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

	//restore functions
	void RestoreAccountList();
	void RestoreGroupsList();  // nu e implementata
	
	Account* getAccount(int ID);
	int GetId(std::string name);
	
	int VerifyExistanceAccount(string,string);
	int VerifyID(int id); // can't have 2 accounts with same iD

	
	void GoOnline(int ID);
	void GoOffine(int ID); // nu e implementata inca
	int getID(string user);
};