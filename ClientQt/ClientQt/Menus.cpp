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
	//	SingUp();
		break;
	case '2':
		//LogIn();
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
	std::cout << "4.See the groups that you are part in!" << std::endl;
	option = _getch();

	switch (option) {
	case '1':
	{
	//	std::string name;
	//	std::cout << "Choose the group name " << std::endl;
	//	std::cin >> name;
	//	CreateGroup(name);
	//	system("cls");
		goto et2;
		break;
	}
	case '2':
	{
		/*string message = "seeinvitation.";
		message.append(std::to_string(this->ID));
		SendString(message);*/
		goto et2;
		break;
	}
	case '3':
	{
		//std::string name;
	//	std::cout << "Group name: " << std::endl;
		//std::cin >> name;
		//this->ConnectToGroup(name);
		//if (this->OKforGroup == true)
		//{
			
	//		this->ViewMenu3(name);
	//		break;
	//	}
	//	else {
			goto et2;
			break;
	//	}
	}
	case '4': {
		/*string message = "seegrouplist.";
		message.append(std::to_string(this->ID));
		SendString(message);
		_getch();*/
		goto et2;
		break;
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
	int option;
	fflush(NULL);
	system("cls");
	std::cout << "1.Send a invitation to a client(Only for owner/admin)\n" << std::endl;
	std::cout << "2.Quick add a client (Only for owner/admin)\n" << std::endl;
	std::cout << "3. Go to chat\n" << std::endl;
	std::cout << "4. Make an user admin\n" << std::endl;
	std::cout << "5.See member list\n" << std::endl;
	std::cout << "6.See admin list\n" << std::endl;
	std::cout << "7.Remove a member from the group\n" << std::endl;
	std::cout << "8.Leave the group\n" << std::endl;
	std::cout << "9. Downgrade an admin\n" << std::endl;
	std::cout << "10. Delete the group(only for owner)\n" << std::endl;
	std::cout << "11. Go to private chat with a member\n" << std::endl;
	std::cout << "12. Go back\n" << std::endl;
	
	cin >> option;
	switch (option) {
	case 1: {
		if (this->Statut == off || this->Statut == normal) {
			std::cout << "You don't have these rights!!!";
			Sleep(1000);
			goto et3;
			break;
		}
		std::string username;
		std::cout << "Insert client name" << std::endl;
		std::cin >> username;
     	std:string aux = "inviteclient";
		aux.append(".");
		aux.append(std::to_string(this->ID));

		aux.append(".");
		aux.append(username);
		aux.append(".");
		aux.append(groupName);
		SendString(aux, true);
		goto et3;
		break;
	}
	case 2:{
		if (this->Statut == off || this->Statut == normal) {
			std::cout << "You don't have these rights!!!";
			Sleep(1000);
			goto et3;
			break;
		}
		std::string username;
		std::cout << "Insert client name" << std::endl;
		std::cin >> username;
		string message = "quickadd.";
		message.append(std::to_string(this->ID));
		message.append(".");
		message.append(groupName);
		message.append(".");
		message.append(username);
		SendString(message, true);
		goto et3;
		break;
	}
		
	case 3:{ 
	      this->InChat = true;
	      this->ChatGroup(groupName);
          break;
	}
	case 11: {
		std::cout << "Insert member name: ";
		string name;
		cin >> name;
		this->InChat = true;
		this->PrivateChat(name, groupName);
		break;
	}
	case 4: {
		if (this->Statut == off || this->Statut == normal) {
			std::cout << "You don't have these rights!!!";
			Sleep(1000);
			goto et3;
			break;
		} 
		std::cout << "Insert client name" << std::endl;
		this->SeeMemeberList(groupName); 
		_getch();
		std::string username;
		std::cout<<endl;
		std::cin >> username;
		std::string message = "makeadmin.";
		message.append(std::to_string(this->ID));
		message.append(".");
		message.append(groupName);
		message.append(".");
		message.append(username);
	
		SendString(message, true);
		goto et3;
		break;
	}
	case 12:{
		system("cls"); 
		this->ViewMenu2();
		break;
	}
	case 5: {
		this->SeeMemeberList(groupName);
		_getch();
		goto et3;
		break;
	}
	case 7: {
		if (this->Statut == off || this->Statut == normal) {
			std::cout << "You don't have these rights!!!";
			Sleep(1000);
			goto et3;
			break;
		}
		std::cout << "Insert client name" << std::endl;
		this->SeeMemeberList(groupName);
		_getch();
		std::string username;
		std::cout << endl;
		std::cin >> username;
		std::string message = "kickmember.";
		message.append(std::to_string(this->ID));
		message.append(".");
		message.append(groupName);
		message.append(".");
		message.append(username);
		message.append(".");
		message.append("kick");
		SendString(message, true);
		goto et3;
		break;

	}
	case 8: {
		std::cout << "Are you sure you want to leave group " << groupName <<"? (y/n) "<< std::endl;
		if (_getch() == 'y') {
			std::string message = "kickmember.";
			message.append(std::to_string(this->ID));
			message.append(".");
			message.append(groupName);
			message.append(".");
			message.append(std::to_string(this->ID));
			message.append(".");
			message.append("leave");
			SendString(message, true);
			system("cls");
			this->ViewMenu2();
			break;
		}
		goto et3;
		break;
	}
	case 9: {
           if (this->Statut !=owner) {
			std::cout << "You are not the owner!!You don't have these rights!";
			Sleep(1000);
			goto et3;
			break;}

		  
		   this->SeeAdminList(groupName);
		   std::cout << "\n type exit to go back!" << std::endl;
		   std::string username;
		   std::cout << endl;
		   std::cin >> username;
		   if (username == "exit") {
			   goto et3;
			   break;
		   }
		   std::cout << "Insert admin name" << std::endl;
		   string Message = "downgradeadmin.";
		   Message.append(std::to_string(this->ID));
		   Message.append(".");
		   Message.append(groupName);
		   Message.append(".");
		   Message.append(username);
		   SendString(Message, true);
		   goto et3;
		   break;
	}


	case 6: {
		this->SeeAdminList(groupName);
		_getch();
		goto et3;
		break;
	}
	case 10: {
		if (this->Statut != owner) {
			std::cout << "You are not the owner!!You don't have these rights!";
			Sleep(1000);
			goto et3;
			break;
		}
		std::cout << "Are you sure you want to delete group " << groupName << "? (y/n) " << std::endl;
		if (_getch() == 'y') {
			string message = "deleteGroup.";
			message.append(std::to_string(this->ID));
			message.append(".");
			message.append(groupName);
			SendString(message, true);



			system("cls");
			this->ViewMenu2();
			break;
		}
		else {
			goto et3;
			break;
		}

	}
	default:
	{
		system("cls");
		goto et3;
	}
	}

}

