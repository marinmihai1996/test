#ifndef _header_24442
#define _header_24442
#include<iostream>
#include"IStatus.h"
class Member:public IStatus
{
protected:
	std::string statut;

public:  
	void SetStatut(std::string sir);
    std::string getstatut();

	virtual bool deleteGroup();
	virtual bool kickMember();
	virtual bool InviteClient();
	virtual bool MakeAdmin();
	virtual bool DowngradeAdmin();
	virtual bool MakeOwner();
	bool OnlyMember();
	Member();
	virtual ~Member();
};

#endif