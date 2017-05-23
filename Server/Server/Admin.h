#ifndef _header_24443
#define _header_24443
#include "Member.h"



class Member;
class Admin : public Member
{
protected: 

public:
	bool kickMember();
	bool InviteClient();
	bool MakeAdmin();
	Admin();
	~Admin();
};
#endif
