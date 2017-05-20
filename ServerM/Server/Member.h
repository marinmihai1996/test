#pragma once
#include<vector>
#include<direct.h>
#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
#include"LogGroups.h"
#include<fstream>
class Member
{
private:
	string statut;

public:
	void SetStatut(string sir) { statut=sir; };
	string getstatut() { return statut; };

	virtual bool deleteGroup() { return false; };
	virtual bool kickMember() { return false; };
	virtual bool InviteClient() { return false; };
	virtual bool MakeAdmin() { return false; };
	virtual bool DowngradeAdmin() { return false; };
	Member();
	~Member();
};

 