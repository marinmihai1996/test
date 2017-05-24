#ifndef _header_24443
#define _header_24443
#include "Member.h"



class Member;
class Admin : public Member
{
protected: 

public:
	

	virtual bool deleteGroup();
	virtual bool kickMember();
	virtual bool InviteClient();
	virtual bool MakeAdmin();
	virtual bool DowngradeAdmin();
	virtual bool MakeOwner();
	Admin();
	~Admin();
};
#endif
