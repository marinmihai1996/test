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
	void RestoreAdminList(Group*);



	Account* getAccount(int ID);
	Account* getAccount(string name);
	Account*getAccount(string accountName, string groupName);
	Group* getGroup(string name);
	int GetId(std::string name);
	void AddAdmin(Group*, Account*);
	
	int VerifyExistanceAccount(string,string,int);
	bool ExistsGroup(string);
	vector<string> GetMemberList(Group*);
	vector<string> GetMemberList(std::string groupName);
	vector<string> GetAdminList(std::string groupName);
	vector<string> GetGroupList(Account*);


	void GoOnline(int ID);
	void GoOffine(int ID); // nu e implementata inca
	void ChangeIdForSingUp(int ID);
	void CleanAccountFile();
	void ChangeIdForLogIn(int ID,string username);

	void deleteGroup(Group*);
	int getGroupNr(std::string name);

	bool VerifyAdminStatus(Account*, Group*);
	
};  