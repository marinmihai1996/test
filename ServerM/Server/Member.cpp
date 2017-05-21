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