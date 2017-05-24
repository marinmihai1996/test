#include"Client.h"



#include"Utils.h"



void Client::CreateGroup(std::string groupName)
{
	std::string CreateGroupMessage = "creategroup";
	std::string ErrorMessage = "Failed to create a group";
	if (!this->SendString(CreateGroupMessage, groupName))
		SendString(ErrorMessage,true);
	this->Statut = owner;
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
	SendString(message,true);
	Sleep(1000);

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
			SendString(message,true);
			std::cout << "you are now in the group" << std::endl;
			
		}
		else if (option == "no") {
			ok = true;
		}
		else {
			std::cout << "try again" << std::endl;
			
		}
	}
}

void Client::SeeMemeberList(std::string groupName) {
	std::string message = "seememberlist.";
	message.append(groupName);
	message.append(".");
	message.append(std::to_string(this->ID));
	SendString(message,true);

}


void Client::SeeAdminList(std::string groupName) {
	std::string message = "seeadminlist.";
	message.append(groupName);
	message.append(".");
	message.append(std::to_string(this->ID));
	SendString(message,true);

}