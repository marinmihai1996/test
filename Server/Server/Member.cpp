#include "Member.h"



Member::Member()
{
	this->SetStatut("member");
}


Member::~Member()
{
}
bool Member:: OnlyMember() {
	this->SetStatut("normal");
	return true;
}

 void Member:: SetStatut(std::string sir) {
	 statut = sir; };

std::string Member:: getstatut() {
	return statut; };

bool Member::deleteGroup() {
	return false; };

bool Member::kickMember() {
	return false; };

bool Member::InviteClient() { 
	return false; };

bool Member::MakeAdmin() { 
	return false; };

bool Member::DowngradeAdmin() {
	return false; };

bool Member::MakeOwner() { 
	return false; };