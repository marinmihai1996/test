
#include"Client.h"

#include"Utils.h"



void Client::PrivateChat(std::string username, std::string groupName)
{
	std::cout << "Type exit to stop chat" << std::endl;
	this->RestoreOfflineMessages(groupName, "private", username);
	char message[256];
	int tryy = 0;

	while (true)
	{
		std::string ChatMessage = "private";
		ChatMessage.append(".");
		ChatMessage.append(groupName);
		ChatMessage.append(".");
		ChatMessage.append(std::to_string(this->ID));
		ChatMessage.append(".");
		ChatMessage.append(username);
		ChatMessage.append(".");
		int size;

		fgets(message, 100, stdin);;
		size = strlen(message);
		message[size - 1] = '\0';
		if (strcmp(message, "exit") == 0) {
			this->InChat = false;
			system("cls");
			break;
		}
		if (tryy != 0)
		{
			//std::cout << "You:";
			std::string Message = message;
			ChatMessage.append(Message);
			if (!SendString(ChatMessage, true)) break;
			Sleep(10);
		}
		tryy++;
	}
	//system("cls");
	this->ViewMenu3(groupName);
	return;

}
void Client::ChatGroup(std::string groupName)
{

	std::cout << "Type exit to stop chat" << std::endl;
	this->RestoreOfflineMessages(groupName, "grup", "all");
	char message[256];
	int tryy = 0;

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
		if (strcmp(message, "exit") == 0) {
			this->InChat = false;
			system("cls");
			break;
		}
		if (tryy != 0)
		{
			//std::cout << "You:";
			std::string Message = message;
			ChatMessage.append(Message);
			if (!SendString(ChatMessage, true)) break;
			Sleep(10);
		}
		tryy++;
	}
	//system("cls");
	this->ViewMenu3(groupName);
	return;

}

void Client::RestoreOfflineMessages(std::string groupName, std::string Case, std::string Username) {

	//restoreMesG.username.groupname
	if (Case == "grup")
	{
		std::string Message = "restoreMesG.";
		Message.append(this->currentUserName);
		Message.append(".");
		Message.append(groupName);
		SendString(Message);
		
	}
	else { //case==privat
		   //restoreMesP.username.groupname.username
		std::string Message = "restoreMesP.";
		Message.append(this->currentUserName);
		Message.append(".");
		Message.append(groupName);
		Message.append(".");
		Message.append(Username);
		SendString(Message);
	}
}
	