#include"Group.h"
using namespace std;
Group::Group(string groupName, string ownerName)
{
	
	this->groupName = groupName;
	this->ownerName = ownerName;
	
	//std::cout << "Group " << groupName<< " requested by the client " << ownerName << " is created. This client is the owner" << std::endl;

}


bool Group::ExistMember(Account* account)
{
	for (int i = 0; i < MemberList.size(); i++) {
		if (MemberList[i] == account) return true;
	}
	return false;
}

void Group::kickMember(std::string name)
 {
	for (int i = 0; i <= MemberList.size(); i++)
	{
		if (MemberList[i]->GetUsername().compare(name))
			MemberList.erase(MemberList.begin() + i);
	}
}
	