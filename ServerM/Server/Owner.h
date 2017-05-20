#pragma once
#include "Member.h"
class Owner :
	public Admin
{
public:
	bool deleteGroup() { return true; };
	bool MakeAdmin();
	bool DowngradeAdmin();
	Owner();
	~Owner();
};

