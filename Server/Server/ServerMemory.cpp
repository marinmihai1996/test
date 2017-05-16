#include<iostream>
#include"ServerMemory.h"
#include <fstream>
#include<vector>


static vector<string> split(const string &text, char sep) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}


Memory* Memory::mpInstance = NULL;
Memory::Memory()
{

}
Memory&Memory::GetInstance()
{
	if (mpInstance == NULL)
	{
		mpInstance = new Memory();
	}
	return *mpInstance;
}

void Memory::ViewGroupsList()
{
	for (int i = 0; i < GroupList.size(); i++)
	{
		std::cout << GroupList[i]->GetGroupName() << std::endl;
	}
}

void Memory::ViewAccountsList()
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		std::cout <<AccountList[i]->GetUsername() << std::endl;
	}
}


Account* Memory::getAccount(int ID)
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		if (AccountList[i]->GetId() == ID)
			return AccountList[i];
	}
	return NULL;
}
void Memory::AddInAccountList(Account*a){

	AccountList.push_back(a);
}

void Memory::AddInGroupList(Group*a){

	GroupList.push_back(a);
}
void Memory::RestoreAccountList() {
	LogClass& Log = LogClass::GetInstance();
	string line;
	ifstream myfile("Accounts.txt");
	if (myfile.good()){
		while (getline(myfile, line)){  // same as: while (getline( myfile, line ).good())
			
			vector<string>tokens = split(line, ' ');
			string username = tokens.at(0);
			string password = tokens.at(1);
			int ID = std::stoi(tokens.at(2));
			Account *newAccount = new Account(username, password,ID);
			this->AddInAccountList(newAccount);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
};


void Memory::RestoreGroupsList() {
	
		LogGroups& Log = LogGroups::GetInstance();
		string line;
		ifstream myfile("Groups.txt");
		if (myfile.good()) {
			while (getline(myfile, line)) {  // same as: while (getline( myfile, line ).good())
				vector<string>tokens = split(line, ' ');
				string groupName = tokens.at(0);
				string ownerName = tokens.at(1);
				Group*group = new Group(groupName,ownerName);
				this->AddInGroupList(group);
			}
			myfile.close();
		}
		else cout << "This server doesn't have any groups yet!\n";

};

void Memory::ChangeIdForSingUp(int ID)
{ 
	if (AccountList.size() == 0) return;
    
	for (int i = 0; i < AccountList.size(); i++) {
		if (AccountList[i]->GetId() == ID) {
			AccountList[i]->SetId(AccountList.size());
			// am schimbat ID-ul celui pe care l-am gasit cu acelasi ID
		}
	}
	
}

void Memory::ChangeIdForLogIn(int ID,string username) {

	if (AccountList.size() == 1) return;

	for (int i = 0; i < AccountList.size(); i++) {
		if (AccountList[i]->GetId() == ID && AccountList[i]->GetUsername() != username) {
			AccountList[i]->SetId(AccountList.size()-1);
			// am schimbat ID-ul celui pe care l-am gasit cu acelasi ID
		}
	}
}
void Memory::CleanAccountFile()
{
	fstream ofs;
	ofs.open("Accounts.txt", ios::out | ios::trunc);
	ofs.flush();
	ofs.close();
	
}
int Memory::GetId(std::string name)
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		if (AccountList[i]->GetUsername().compare(name))
			return AccountList[i]->GetId();
	}
}

int Memory::VerifyExistanceAccount(string usename, string pass,int ID)  
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		if (!AccountList[i]->GetUsername().compare(usename)){

			if (!AccountList[i]->GetPassword().compare(pass)) {
				AccountList[i]->SetId(ID); // schimb Id-ul si in memorie
				return 1; // deja exista
			}
			else return 2; // exista unul cu acelasi username
		}
	}
	return 0;
}
bool Memory::ExistsGroup(string groupName)
{
	for (int i = 0; i < GroupList.size(); i++) {
		if (GroupList[i]->GetGroupName() == groupName) return true;
	}
	return false;
}
void Memory::GoOnline(int ID)
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		if (AccountList[i]->GetId() == ID) {
			AccountList[i]->GoOnline();
			break;
		}
	}
}

void Memory::deleteGroup(int i)
{
	GroupList.erase(GroupList.begin()+i);
}


int Memory::getGroupNr(std::string name)
{
	for (int i = 0; i < GroupList.size(); i++)
	{
		if (GroupList[i]->GetGroupName().compare(name) == 0)
		{
			return i;
		}
	}
}

Group* Memory::getGroup(std::string name)
{
	for (int i = 0; i < GroupList.size(); i++)
	{
		if (GroupList[i]->GetGroupName().compare(name) == 0)
		{
			return GroupList[i];
		}
	}
	return NULL;
}