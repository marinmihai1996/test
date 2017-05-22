#include<iostream>
#include"ServerMemory.h"
#include <fstream>
#include<vector>


bool is_emptyy(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

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


Account* Memory::getAccount(string name)
{
	for (int i = 0; i < AccountList.size(); i++)
	{
		if (AccountList[i]->GetUsername() == name)
			return AccountList[i];
	}
	return NULL;
}

Group*Memory::getGroup(string name) {

	for (int i = 0; i < GroupList.size(); i++) {
		if (GroupList[i]->GetGroupName() == name)
			return GroupList[i];
	}
	return NULL;
}

void Memory::AddInAccountList(Account*a){

	AccountList.push_back(a);
}
void Memory::RestoreGroupAccountsList(Group*group)
{
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	std::string groupName = group->GetGroupName();
	path.append(groupName);
	path.append(".txt");
	ifstream InFile(path); // deschid fisierul grupului unde se afla membrii
	string line;
	if (InFile.good()) {
		while (getline(InFile, line)) {
			string username = line;;
			Account *account = this->getAccount(username);
			group->addAccount(account);
		}
	}
}
void Memory::AddInGroupList(Group*group){

	GroupList.push_back(group); 
	this->RestoreGroupAccountsList(group); // pentru fiecare grup, fac restore la account-urile membre
}
void Memory::RestoreAccountList() {
	LogClass& Log = LogClass::GetInstance();
	string line;
	ifstream myfile("C:/Users/Maria/Documents/git/test/Server/Server/Accounts.txt");
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

void Memory::RestoreAdminList(Group*group){
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	string name = group->GetGroupName();
	path.append(name);
	path.append(".adminList.txt");
	ifstream file(path);
	if (is_emptyy(file) || !file) return;
	ifstream filee;
	filee.open(path);
	string line;
	while (std::getline(filee, line))
	{
		Account *a = this->getAccount(line);
		
		this->AddAdmin(group, a);
	}
	

}
void Memory::RestoreGroupsList() {
	
		LogGroups& Log = LogGroups::GetInstance();
		string line;
		ifstream myfile("C:/Users/Maria/Documents/git/test/Server/Server/Groups.txt");
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
bool find(int a, int *v,int nr) {
	for (int i = 0; i < nr; i++) {
		if (v[i] == a) return true;
	}
	return false;
}
void Memory::ChangeIdForSingUp(int ID)
{ 
	if (AccountList.size() == 0) return;
	int* vector = new int[AccountList.size()];
	for (int i = 0; i < AccountList.size(); i++) {
		vector[i] = AccountList[i]->GetId();
	}
	for (int i = 0; i < AccountList.size(); i++) {
		if (AccountList[i]->GetId() == ID) {
			int a = 0;
			while (find(a, vector, AccountList.size()) == true) a++;	
			AccountList[i]->SetId(a);
			// am schimbat ID-ul celui pe care l-am gasit cu acelasi ID
		}
	}
	delete[AccountList.size()] vector;
}

void Memory::ChangeIdForLogIn(int ID,string username) {

	if (AccountList.size() == 1) return;
	int* vector = new int[AccountList.size()];
	for (int i = 0; i < AccountList.size(); i++) {
		vector[i] = AccountList[i]->GetId();
	}
	for (int i = 0; i < AccountList.size(); i++) {
		if (AccountList[i]->GetId() == ID && AccountList[i]->GetUsername() != username) {
			int a = 0;
			while (find(a, vector, AccountList.size()) == true) a++;
			AccountList[i]->SetId(a);
			// am schimbat ID-ul celui pe care l-am gasit cu acelasi ID
		}
	}
	delete [AccountList.size()] vector;

}
void Memory::CleanAccountFile()
{
	fstream ofs;
	ofs.open("C:/Users/Maria/Documents/git/test/Server/Server/Accounts.txt", ios::out | ios::trunc);
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


void Memory::deleteGroup(Group*a)
{
	for (int i = 0; i < GroupList.size(); i++)
	{
		if (a->GetGroupName() == GroupList[i]->GetGroupName())
		{
			GroupList.erase(GroupList.begin() + i);
			return;
		}
	}
	
}


int Memory::getGroupNr(std::string name)
 {
	for (int i = 0; i < GroupList.size(); i++)
		 if (GroupList[i]->GetGroupName().compare(name) == 0)
			return i;		
}

vector<string> Memory::GetMemberList(Group*group) {
	vector<string> tokens;
	for (int i = 0; i < GroupList.size(); i++)
	{
		if (GroupList[i]->GetGroupName() == group->GetGroupName()) {
			tokens = GroupList[i]->GetMemberList();
		}
	}
	return tokens;
}

vector<string> Memory::GetMemberList(std::string groupName) {
	vector<string> tokens;
	for (int i = 0; i < GroupList.size(); i++)
	{
		if (GroupList[i]->GetGroupName() == groupName) {
			tokens = GroupList[i]->GetMemberList();
		}
	}
	return tokens;
}

vector<string> Memory::GetAdminList(std::string groupName) {
	vector<string> tokens;
	for (int i = 0; i < GroupList.size(); i++)
	{
		if (GroupList[i]->GetGroupName() == groupName) {
			tokens = GroupList[i]->GetAdminList();
		}
	}
	return tokens;
}

Account*Memory::getAccount(string accountName, string groupName) {


	for (int i = 0; i < GroupList.size(); i++) {
		if (GroupList[i]->GetGroupName() == groupName) {
			Account*a = GroupList[i]->getAccount(accountName);
			return a;
		}
	}
}

void Memory::AddAdmin(Group*group, Account *a)
{
	for (int i = 0; i < GroupList.size(); i++) {
		if (group->GetGroupName() == GroupList[i]->GetGroupName()) {
			GroupList[i]->addAdmin(a);
			return;
		}
	}
}

bool Memory::VerifyAdminStatus(Account*a, Group*g) {
	for (int i = 0; i < GroupList.size(); i++) {
		if (GroupList[i]->GetGroupName() == g->GetGroupName()) {
			if (GroupList[i]->ExistAdmin(a) == true) return true;
			else return false;
		}
	}
}

vector<string> Memory::GetGroupList(Account*a) {
	
	vector<string>tokens;
	for (int i = 0; i < GroupList.size(); i++) {
		if (GroupList[i]->ExistMember(a) == true) {
			tokens.push_back(GroupList[i]->GetGroupName());
		}
	}
	return tokens;
 
}