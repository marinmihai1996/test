#ifndef _header_24444
#define _header_24444
#include"Member.h"

class Member;
class Owner :public Member
{
public:
	bool deleteGroup();
	bool MakeAdmin();
	bool DowngradeAdmin();
	bool kickMember();
	bool InviteClient();
	bool MakeOwner();
	Owner();
	~Owner();
};

#endif