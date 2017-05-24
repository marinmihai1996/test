#pragma once
#include<iostream>
class IStatus {


protected:
	std::string statut;
public:
	virtual void SetStatut(std::string sir) = 0;
	virtual std::string getstatut() = 0;
	virtual bool LeaveGroup(std::string name) = 0;
	virtual bool deleteGroup() = 0;
	virtual bool kickMember() = 0;
	virtual bool InviteClient() = 0;
	virtual bool MakeAdmin() = 0;
	virtual bool DowngradeAdmin() = 0;
	virtual bool MakeOwner() = 0;
};