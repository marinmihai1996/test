#include"Client.h"
#include<iostream>
#include<string>
using namespace std;



void Client::ViewMenu1()
{
	fflush(NULL);
	//std::cout << "ID=" << ID << std::endl;
	std::cout << "MENU" << std::endl;
	int option;

	std::cout << "1. SingUp" << std::endl;
	std::cout << "2. LogIn" << std::endl;
	
	std::cin >> option;
	switch (option)
	{
	case 1:
		SingUp();
		break;
	case 2:
		LogIn();
		break;
	case 3:
	{string name;
	std::cout << "Choose the group name " << std::endl;
	std::cin >> name;
	CreateGroup(name);
	break;
	}
	default:
		break;
	}
}

/*


void Client::ViewMenu2() {
int option;
fflush(NULL);
std::cout << "1.Create a group" << std::endl;
std::cout << "2.See your group invitation" << std::endl;
std::cout << "3. Acces a group.You have to be a member first." << std::endl;

std::cin >> option;
switch (option)
{
case 1:
{std::string name;
std::cout << "Choose the group name " << std::endl;
std::cin >> name;
CreateGroup(name);
break; }
case 2:
//LogIn();
break;

default:
break;
}
}





*/