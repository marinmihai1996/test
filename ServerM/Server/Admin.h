#pragma once
#include "Member.h"
class Admin :
	public Member
{
protected: 

public:
	bool kickMember() { return true; };
	bool InviteClient();
	Admin();
	~Admin();
};

