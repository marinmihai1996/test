#include"Client.h"
#include<iostream>
#include<string>
#include<conio.h>
using namespace std;



void Client::ViewMenu1()
{
	et:
	fflush(NULL);
	//std::cout << "ID=" << ID << std::endl;
	std::cout << "MENU" << std::endl;
	//int option;

	std::cout << "1. SingUp" << std::endl;
	std::cout << "2. LogIn" << std::endl;
	
	//std::cin >> option;
	char option;
	option =_getch();
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
		system("cls");
		goto et; }
	}
}


void Client::ViewMenu2() {

	et2:
  // int option;
   fflush(NULL);
   std::cout << "1.Create a group" << std::endl;
   std::cout << "2.See your group invitation" << std::endl;
   std::cout << "3. Acces a group.You have to be a member first." << std::endl;

  // std::cin >> option;
   char option;
   option = _getch();
       switch (option){
       case '1':
	   {
		   std::string name;
		   std::cout << "Choose the group name " << std::endl;
		   std::cin >> name;
		   CreateGroup(name);
		   break; }
	   case '2':
		   break;
	   default:
	   {
		   system("cls");
		   goto et2; }
	   }
}

void Client::ViewMenu3(string &groupName) {
	et3:
	//int option;
	fflush(NULL);
	std::cout << "1.Send a invitation to a client\n" << std::endl;
	std::cout << "2.Quick add a client\n" << std::endl;
	std::cout << "3. Go to chat\n" << std::endl;
	std::cout << " 4. Go back\n" << std::endl;
	//std::cin >> option;
	char option;
	option = _getch();
	switch (option) {
	case '1':
	{
		std::string name;
		std::cout << "Insert client name" << std::endl;
		std::cin >> name;
    	std:string aux = "inviteclient";
		aux.append(name);
		aux.append(".");
		std::string namegroup = groupName;
		this->SendString(aux, namegroup);
		break; }
	case '2':
		break;
	case '3':
		this->ChatGroup(groupName);
	case '4':
	{
		system("cls");
		this->ViewMenu2(); }
	default:
	{
		system("cls");
		goto et3; }
	}
}


