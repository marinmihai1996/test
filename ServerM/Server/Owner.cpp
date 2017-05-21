#include "Owner.h"



Owner::Owner()
{
	SetStatut("owner");
}


Owner::~Owner()
{
}

bool Owner::kickMember()
{
	return true;
}
bool Owner::MakeAdmin()
{
	return true;
}
bool Owner::InviteClient()
{
	return true;
}
bool Owner::DowngradeAdmin()
{
	
	return true;
}
bool Owner::deleteGroup()
{
	return true;
}

bool Owner:: MakeOwner() { 
	this->SetStatut("owner");
	return true;

};

