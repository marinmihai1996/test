#pragma once
#include<string>
using namespace std;
class Account
{
private:
	string username;
	string password;

public:
	string GetUsername() { return this->username; };
	string GetPassword() { return this->password; };
	Account(string name, string pass);
	
};
