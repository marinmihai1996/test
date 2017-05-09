#include"Client.h"

#include<iostream>


void Client::CreateGroup(std::string groupName)
{
	std::string CreateGroupMessage = "creategroup";
	std::string ErrorMessage = "Failed to create a group";
	if (!this->SendString(CreateGroupMessage, groupName))
		SendString(ErrorMessage);

	Sleep(10);

}