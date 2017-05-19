#include"Client.h"

#include<iostream>
#include<conio.h>
#include<vector>
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
	Sleep(1000);


}

void Client::ChatGroup(std::string groupName)
{
	char message[256];
	int tryy = 0;
	std::cout << "Type exit to stop chat" << std::endl;
	while (true)
	{
		std::string ChatMessage = "chatg";
		ChatMessage.append(".");
		ChatMessage.append(groupName);
		ChatMessage.append(".");
		ChatMessage.append(std::to_string(this->ID));
		ChatMessage.append(".");
		int size;
	
		fgets(message, 100, stdin);;
		size = strlen(message);
		message[size - 1] = '\0';
		if (strcmp(message,"exit")==0) { 
			this->InChat = false;
			system("cls");
			break;
		}
		if (tryy != 0)
		{
			//std::cout << "You:";
			std::string Message = message;
			ChatMessage.append(Message);
			if (!SendString(ChatMessage)) break;
			Sleep(10);
		}
		tryy++;
	}
	//system("cls");
	this->ViewMenu3(groupName);
	return;
	
}


void Client::ProcessInvitation(std::string group)
{
	bool ok = false;
	while (ok == false)
	{
		system("cls");  
		std::string option;
		std::cout << "Do you wanna join group " << group << "? ( yes/no )" << std::endl;
		fflush(NULL);
		std::cin >> option;
		std::cin.sync();
		if (option == "yes") {
			ok = true;
			std::string message = "joingroup.";
			message.append(group);
			message.append(".");
			message.append(std::to_string(this->ID));
			SendString(message);
			std::cout << "you are now in the group" << std::endl;
			//Sleep(1000);
		}
		else if (option == "no") {
			ok = true;
		}
		else {
			std::cout << "try again" << std::endl;
			
		}
	}
}