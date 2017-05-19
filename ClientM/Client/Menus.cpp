#include"Client.h"
#include<iostream>
#include<string>
#include<conio.h>

using namespace std;

void Client::ViewMenu1()
{
et:
	fflush(NULL);
	
	std::cout << "MENU" << std::endl;

	std::cout << "1. SingUp" << std::endl;
	std::cout << "2. LogIn" << std::endl;

	char option;
	option = _getch();
	switch (option)
	{
	case '1':
		SingUp();
		break;
	case '2':
		LogIn();
		break;
	default:
	{
		system("cls"); }
	goto et;
	}
}



void Client::ViewMenu2() { // ai de sters aici

et2:
	system("cls");
	cin.clear();
	cin.sync();
	char option;
	fflush(NULL);
	//system("cls");
	std::cout << "1.Create a group" << std::endl;
	std::cout << "2.See your group invitations" << std::endl;
	std::cout << "3. Acces a group.You have to be a member first." << std::endl;
	option = _getch();

	switch (option) {
	case '1':
	{
		std::string name;
		std::cout << "Choose the group name " << std::endl;
		std::cin >> name;
		CreateGroup(name);
		system("cls");
		goto et2;
		break;
	}
	case '2':
	{
		string message = "seeinvitation.";
		message.append(std::to_string(this->ID));
		SendString(message);
		goto et2;
		break;
	}
	case '3':
	{
		std::string name;
		std::cout << "Group name: " << std::endl;
		std::cin >> name;
		this->ConnectToGroup(name);
		if (this->OKforGroup == true)
		{
			this->ViewMenu3(name);
			break;
		}
		else {
			goto et2;
			break;
		}
	}
	
	default:
	{
		system("cls");
		goto et2;
	}
	}
}

void Client::ViewMenu3(string &groupName) {
et3:
	cin.clear();
	cin.sync();
	char option;
	fflush(NULL);
	system("cls");
	std::cout << "1.Send a invitation to a client(Only for owner/admin)\n" << std::endl;
	std::cout << "2.Quick add a client (Only for owner/admin)\n" << std::endl;
	std::cout << "3. Go to chat\n" << std::endl;
	std::cout << "4. Go back\n" << std::endl;

	option = _getch();
	switch (option) {
	case '1': {

		std::string username;
		std::cout << "Insert client name" << std::endl;
		std::cin >> username;
	std:string aux = "inviteclient";
		aux.append(".");
		aux.append(username);
		aux.append(".");
		aux.append(groupName);
		SendString(aux);
		goto et3;
		break;
	}
	case '2':
		break;
	case '3':
	{ 
	      this->InChat = true;
	      this->ChatGroup(groupName);
          break;
	}
	case '4':
	{
		system("cls");
		this->ViewMenu2();
		break;
	}
	default:
	{
		system("cls");
		goto et3;
	}
	}

}

