#include"Group.h"
using namespace std;
Group::Group(string groupName, string ownerName)
{
	Memory&mem = Memory::GetInstance();
	this->groupName = groupName;
	this->ownerName = ownerName;
	

}


bool Group::ExistMember(Account* account)
{
	for (int i = 0; i < MemberList.size(); i++) {
		if (MemberList[i] == account) return true;
	}
	return false;
}
bool Group::ExistAdmin(Account* account)
{
	for (int i = 0; i < AdminList.size(); i++) {
		if (AdminList[i] == account) return true;
	}
	return false;
}


bool Group::kickMember(std::string name)
 {
	for (int i = 0; i < MemberList.size(); i++)
	{
		if (MemberList[i]->GetUsername()==name)
		{
			
			MemberList.erase(MemberList.begin() + i);
			return true;
		}
	}
	return false;
}
bool Group::kickAdmin(std::string name)
{
	for (int i = 0; i < AdminList.size(); i++)
	{
		if (AdminList[i]->GetUsername() == name)
		{

			AdminList.erase(AdminList.begin() + i);
			return true;
		}
	}
	return false;
}

vector<string>Group::GetMemberList() {
	vector<string> tokens;
	for (int i = 0; i < this->MemberList.size(); i++) {
		if(this->MemberList[i]!=NULL)
		tokens.push_back(this->MemberList[i]->GetUsername());
	}
	return tokens;
} 
vector<string>Group::GetAdminList() {
	vector<string> tokens;
	for (int i = 0; i < this->AdminList.size(); i++) {
		if (this->AdminList[i] != NULL)
			tokens.push_back(this->AdminList[i]->GetUsername());
	}
	return tokens;
}

Account* Group::getAccount(string accountName){
	for (int i = 0; i < MemberList.size(); i++) {
		if (MemberList[i]->GetUsername() == accountName)
			return MemberList[i];
	}

}

