#include "Admin.h"


Admin::Admin()
{
	this->SetStatut("admin");
}


Admin::~Admin()
{
}
bool Admin::InviteClient()
{
	return true;
}
bool Admin::kickMember()
{
	return true;
}
bool Admin::MakeAdmin()
{
	this->SetStatut("admin");
	return false;
};