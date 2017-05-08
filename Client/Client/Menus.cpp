#include"Client.h"
#include<iostream>
#include<string>
using namespace std;



void Client::ViewMenu1()
{
	
	//std::cout << "ID=" << ID << std::endl;
	std::cout << "MENU" << std::endl;
	int option;

	std::cout << "1. SingUp" << std::endl;
	std::cout << "2. LogIn" << std::endl;
	//std::cout << "3. Create a group" << std::endl;
	/*std::cout << "1. LogIn" << std::endl;
	std::cout << "1. LogIn" << std::endl;
	std::cout << "1. LogIn" << std::endl;*/
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