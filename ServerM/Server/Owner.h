#pragma once
#include "Member.h"
class Owner :
	public Member
{
public:
	bool deleteGroup() { return true; };
	bool kickMember() { return true; };
	bool InviteClient();
	bool MakeAdmin();
	bool DowngradeAdmin();
	Owner();
	~Owner();
};

