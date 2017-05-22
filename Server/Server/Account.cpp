#include"Account.h"

Account::Account(string name,string pass,int id)
{
	this->username = name;
	this->password = pass;
	this->ID = id;
	this->stat = Offline;
}

 
 