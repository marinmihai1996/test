#include"Group.h"
using namespace std;
Group::Group(int ID,string name)
{
	this->OwnerID = ID;
	this->GroupName = name;
	
	std::cout << "Group " << name << " requested by the client " << ID << " is created. This client is the owner" << std::endl;

}