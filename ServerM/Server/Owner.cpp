#include "Owner.h"



Owner::Owner()
{
	this->SetStatut("owner");
}


Owner::~Owner()
{
}


bool Owner::MakeAdmin()
{
	return true;
}

bool Owner::DowngradeAdmin()
{
	return true;
}

bool Owner::InviteClient()
{
	return true;
}
