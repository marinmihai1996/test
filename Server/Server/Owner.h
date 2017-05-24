#ifndef _header_24444
#define _header_24444
#include"Member.h"

class Member;
class Owner :public Member
{
public:
	virtual bool deleteGroup();
	virtual bool kickMember();
	virtual bool InviteClient();
	virtual bool MakeAdmin();
	virtual bool DowngradeAdmin();
	virtual bool MakeOwner();
	Owner();
	~Owner();
};

#endif