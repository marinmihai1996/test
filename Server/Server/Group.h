#pragma once
#include<string>
#include<iostream>
using namespace std;
class Group
{
private:
	string GroupName;
	int OwnerID;
public:
	Group(int ID,string name);
	string GetGroupName() { return this->GroupName; };
	string SetGroupName();
	int GetOwnerId() { return this->OwnerID; };
	


};
