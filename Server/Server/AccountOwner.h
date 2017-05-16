#pragma once
#include "Account.h"
class AccountOwner :
	public Account
{
private:


public:
	void promoteAdmin();
	bool kickMember();
	bool deleteGroup();
};

