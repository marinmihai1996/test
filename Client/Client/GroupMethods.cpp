#include"Client.h"

#include<iostream>


void Client::CreateGroup(std::string groupName)
{
	std::string CreateGroupMessage = "creategroup";
	std::string ErrorMessage = "Failed to create a group";
	if (!this->SendString(CreateGroupMessage, groupName))
		SendString(ErrorMessage);
	std::cout << "You are the owner of " << groupName << std::endl;
	Sleep(2000);
	system("cls");
	fflush(NULL);
	this->ViewMenu3(groupName);



	Sleep(10);

}