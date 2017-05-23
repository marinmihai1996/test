#include"Client.h"

#include<iostream>
#include<conio.h>
#include<vector>
#include<fstream>
using namespace std;
bool is_emptyy(std::ifstream& pFile);

bool deleteFromFile(string name, string FileName) {
	bool exist = false;
	vector<string> BackUpVector;
	string file = FileName.append(".txt");
	string line;
	ifstream InFile(file);
	if (InFile.good()) {
		while (getline(InFile, line)) {
			if (line == name || line.find(name) != string::npos) exist = true;
			else  BackUpVector.push_back(line);
		}
	}
	if (exist == true)
	{
		InFile.close();
		std::ofstream ofs;
		ofs.open(file, std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream OutPut;
		OutPut.open(file, std::ofstream::out | std::ofstream::app);
		for (int i = 0; i < BackUpVector.size(); i++) {
			OutPut << BackUpVector[i];
			OutPut << "\n";
		}
	}
	return exist;
}
void Client::CreateGroup(std::string groupName)
{
	GroupCreated = false;
	std::string CreateGroupMessage = "creategroup";
	std::string ErrorMessage = "Failed to create a group";
	if (!this->SendString(CreateGroupMessage, groupName))
		SendString(ErrorMessage, true);
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
	SendString(message, true);
	Sleep(1000);

}
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
	this->RestoreOfflineMessages(groupName,"grup","all");
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
			if (!SendString(ChatMessage, true)) break;
			Sleep(10);
		}
		tryy++;
	}
	//system("cls");
	this->ViewMenu3(groupName);
	return;
	
}


void Client::ProcessInvitation(std::string cale,std::string name)
{
	//bool ok = false;
	//while (ok == false)
	//{
	//	system("cls");  
	//	std::string option;
	//	//std::cout << "Do you wanna join group " << group << "? ( yes/no )" << std::endl;
	//	fflush(NULL);
	//	std::cin >> option;
	//	std::cin.sync();
	//	if (option == "yes") {
	//		ok = true;
	//		std::string message = "joingroup.";
	//		message.append(group);
	//		message.append(".");
	//		message.append(std::to_string(this->ID));
	//		SendString(message);
	//		//std::cout << "you are now in the group" << std::endl;
	//		//Sleep(1000);
	//	}
	//	else if (option == "no") {
	//		ok = true;
	//	}
	//	else {
	//		std::cout << "try again" << std::endl;
	//		
	//	}
	//}
	bool exist = false;
	vector<string> BackUpVector;
	string file = cale;
	string line;
	ifstream InFile(file);
	if (InFile.good()) {
		while (getline(InFile, line)) {
			if (line == name || line.find(name) != string::npos) exist = true;
			else  BackUpVector.push_back(line);
		}
	}
	if (exist == true)
	{
		InFile.close();
		std::ofstream ofs;
		ofs.open(file, std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream OutPut;
		OutPut.open(file, std::ofstream::out | std::ofstream::app);
		for (int i = 0; i < BackUpVector.size(); i++) {
			OutPut << BackUpVector[i];
			OutPut << "\n";
		}
	}

}
void Client::RestoreOfflineMessages(std::string groupName, std::string Case, std::string Username) {
	std::string path;
	path = this->FolderPath;
	//path.append("/");
	path.append(groupName);
	if (Case == "grup") {

		path.append(".txt");
		std::ifstream file(path);
		if (is_emptyy(file) || !file) return;
		else {
			std::ifstream filee;
			filee.open(path);
			std::string line;

			while (std::getline(filee, line))
			{
				std::cout << line << std::endl;
			}
			filee.close();
			std::ofstream ofs;
			ofs.open(path, std::ofstream::out | std::ofstream::trunc);
			ofs.close();
			return;
		}
	}
	if (Case == "private") {
		

		path.append(".private");
		string pathh = path;
		path.append(".txt");
		std::ifstream file(path);
		if (is_emptyy(file) || !file) return;
		else {
			std::ifstream filee;
			filee.open(path);
			std::string line;

			while (std::getline(filee, line))
			{
				if (line.find(Username) != string::npos)
				{
					std::cout << line << std::endl;
					deleteFromFile(line, pathh);
				}
			}
			filee.close();
		}

	}
}

void Client::SeeMemeberList(std::string groupName) {
	std::string message = "seememberlist.";
	message.append(groupName);
	message.append(".");
	message.append(std::to_string(this->ID));
	SendString(message, true);

}


void Client::SeeAdminList(std::string groupName) {
	std::string message = "seeadminlist.";
	message.append(groupName);
	message.append(".");
	message.append(std::to_string(this->ID));
	SendString(message, true);

}