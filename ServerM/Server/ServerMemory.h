#pragma once
#include<iostream>
#include"Group.h"
#include"Account.h"
#include<deque>
#include"LogAccounts.h"
#include"LogGroups.h"
#include"Server.h"
using namespace std;

class Account;
class Group;
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
	int GetAccountListSize() { return AccountList.size(); };
	
	void ViewGroupsList();
	void ViewAccountsList();
	
	Account* getAccountForIndex(int index) { return AccountList[index]; };
	void AddInGroupList(Group*);
	void AddInAccountList(Account*);

	//restore functions
	void RestoreAccountList();
	void RestoreGroupsList();  
	void RestoreGroupAccountsList(Group*);
	
	Account* getAccount(int ID);
	Account* getAccount(string name);
	Group* getGroup(string name);
	int GetId(std::string name);
	
	int VerifyExistanceAccount(string,string,int);
	bool ExistsGroup(string);// daca grupul exista sau exista un grup cu acelasi nume
	vector<string> GetMemberList(Group*);



	void GoOnline(int ID);
	void GoOffine(int ID); // nu e implementata inca
	void ChangeIdForSingUp(int ID);
	void CleanAccountFile();
	void ChangeIdForLogIn(int ID,string username);

	void deleteGroup(int a);
	int getGroupNr(std::string name);
	
};  