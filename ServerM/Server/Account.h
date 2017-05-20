#pragma once
#include "Member.h"
#include<string>
using namespace std;
class Member;
enum Status {
	Online,
	Offline
};
class Account
{
private:
	string username;
	string password;
	int ID;
	Status stat;
	

public:
	Member *Rights;
	string GetUsername() { return this->username; };
	string GetPassword() { return this->password; };
	int GetId() { return this->ID; };
	void SetId(int ID) { this->ID = ID; };
	Account(string name, string pass,int iD);
	void GoOnline() { this->stat = Online; };
	void GoOffine() {this->stat = Offline; };
};
