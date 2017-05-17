#include"Client.h"

#include<iostream>


void Client::CreateGroup(std::string groupName)
{
	std::string CreateGroupMessage = "creategroup";
	std::string ErrorMessage = "Failed to create a group";
	if (!this->SendString(CreateGroupMessage, groupName))
		SendString(ErrorMessage);
	
	Sleep(2000);
	system("cls");
	fflush(NULL);

	Sleep(10);

}
void Client::ConnectToGroup(std::string groupName) {

	this->OKforGroup = false;
	std::string message = "access";
	message.append(".");
	message.append(groupName);
	message.append(".");
	message.append(std::to_string(this->ID));
	SendString(message);



}

void Client::ChatGroup(std::string groupName)
{
	Client *myClient = this;
	std::string userinput;
	std::cout << "Type exit to stop chat" << std::endl;
	while (userinput!="exit")
	{
		std::string ChatMessage = "chatg";
		ChatMessage.append(".");
		ChatMessage.append(std::to_string(this->ID));
		ChatMessage.append(".");
		std::cin >> userinput;
		ChatMessage.append(userinput);
		std::cout << std::endl;
		if (!myClient->SendString(ChatMessage)) break;
		Sleep(10);
	}
	system("cls");
	//this->ViewMenu3(groupName);
	
}