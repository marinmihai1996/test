#pragma once
#include "Member.h"
class Admin :
	public Member
{
private: 

public:
	bool kickMember() { return true; };
	bool InviteClient();
	Admin();
	~Admin();
};

