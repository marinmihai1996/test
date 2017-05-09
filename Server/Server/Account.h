#pragma once
#include<string>
using namespace std;

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
	string GetUsername() { return this->username; };
	string GetPassword() { return this->password; };
	int GetId() { return this->ID; };
	Account(string name, string pass,int iD);
	void GoOnline() { this->stat = Online; };
	void GoOffine() {this->stat = Offline; };
};
