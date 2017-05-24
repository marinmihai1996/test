#include "Admin.h"


Admin::Admin()
{
	this->SetStatut("admin");
}


Admin::~Admin()
{
}


bool Admin::deleteGroup() {
	return false;
};

bool Admin::kickMember() {
	return true;
};

bool Admin::InviteClient() {
	return true;
};

bool Admin::MakeAdmin() {
	return true;
};

bool Admin::DowngradeAdmin() {
	return false;
};

bool Admin::MakeOwner() {
	return true;
};