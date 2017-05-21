#ifndef _header_24442
#define _header_24442
#include<iostream>
class Member
{
protected:
	std::string statut;

public:
    void SetStatut(std::string sir) { statut=sir; };
	std::string getstatut() { return statut; };

	virtual bool deleteGroup() { return false; };
	virtual bool kickMember() { return false; };
	virtual bool InviteClient() { return false; };
	virtual bool MakeAdmin() { return false; };
	virtual bool DowngradeAdmin() { return false; };
	virtual bool MakeOwner() { return false; };
	bool OnlyMember();
	Member();
	virtual ~Member();
};

#endif