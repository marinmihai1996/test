#include"Group.h"
using namespace std;
Group::Group(string groupName, string ownerName)
{
	
	this->groupName = groupName;
	this->ownerName = ownerName;
	
	std::cout << "Group " << groupName<< " requested by the client " << ownerName << " is created. This client is the owner" << std::endl;

}