#include "Client.h"
#include<conio.h>
#include<iostream>
#include<fstream>
#include <direct.h>
using namespace std;
#include<vector>


static vector<string> split(const string &text, char sep) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}
bool is_emptyy(std::ifstream& pFile)	
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}


bool Client::ProcessPacket(Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage: //If packet is a chat message packet
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		if (Message.find("Connected") != string::npos) {
			
			break;
		}
		if (Message.find("ID") != string::npos) {
			vector<string> tokens = split(Message, '.');
			this->ID = stoi(tokens.at(1));
			break;
		}
		if (Message.find("You are now online") != string::npos) {
			this->OkSingUp = true;
			//std::cout << Message << std::endl;
			break;
		}
		if (Message.find("groupCreated") != string::npos) {
			vector<string> tokens = split(Message, '.');
			string groupName = tokens.at(1);
		//	std::cout << "The group " << groupName << " is created" << std::endl;
			GroupCreated = true;
			fflush(NULL);
			break;
		}
		
		if (Message.find("InGroup") != string::npos) { 
			vector<string> tokens = split(Message, '.');
			string groupName = tokens.at(1);
			this->OKforGroup = true;
			fflush(NULL);
			break;
		}
		if (Message.find("statut") != string::npos) {
			vector<string> tokens = split(Message, '.');
			if (tokens.at(1) == "owner")
				this->Statut = owner;
			else if (tokens.at(1) == "admin") this->Statut = admin;
			else this->Statut = normal;
			break;
		}
		if (Message.find("members") != string::npos) {
			Members = Message;
			//vector<string> tokens = split(Message, '.');
			////std::cout << "The members are: " << std::endl;
			//for (int i = 1; i < tokens.size(); i++) {
			//	//std::cout << tokens[i];
			//	//std::cout << " ";
			//}
			//std::cout << endl;
			//
			break;
		}
		if (Message.find("admins") != string::npos) {
			Admins = Message;
			/*vector<string> tokens = split(Message, '.');
			if (tokens.size() == 1) {
				std::cout << "This group do not has admins " << std::endl;
				break;
			}
			std::cout << "The admins are: " << std::endl;
			for (int i = 1; i < tokens.size(); i++) {
				std::cout << tokens[i];
				std::cout << " ";
			}
			std::cout << endl;

			break;*/
		}
		if (Message.find("currentUser") != string::npos) {
			vector<string> tokens = split(Message, '.');
			this->currentUserName = tokens.at(1);
			_mkdir(currentUserName.c_str());
			break;
		}
		if (Message.find("invitations.txt") != string::npos) {
			mCaleInv = Message;
			//Sleep(1000);
			ifstream file(Message);
			if (is_emptyy(file) || !file)
			{
				std::cout<<endl;
				//std::cout << "You don't have any invitations." << std::endl;
				
				break;
			}
			else
			{
				ifstream filee;
				filee.open(Message);
				string line;
				while (std::getline(filee, line))
				{
					Invitations.append(line);
					Invitations.append(".");
				//this->ProcessInvitation(line);

				}
				filee.close();
				// sterg invitatiile din fisier
				/*std::ofstream ofs;
				ofs.open(Message, std::ofstream::out | std::ofstream::trunc);
				ofs.close();*/


				break;
			}
		}

		if (Message.find("groupList") != string::npos) {
			Groups = Message;
			vector<string> tokens = split(Message, '.');
			if (tokens.size() == 1) {
				//std::cout << "You are not part of any group " << std::endl;
				break;
			}
			//std::cout << "The groups are: " << std::endl;
			for (int i = 1; i < tokens.size(); i++) {
				//std::cout << tokens[i];
				//std::cout << " ";
			}
			//std::cout << endl;
			break;
		
		}
		if (Message.find("chatg") != string::npos) {
			mSemafor = true;
			vector<string> tokens = split(Message, '.');
			string groupName = tokens.at(1);
			string source = tokens.at(2);
			string UserNameDestination = tokens.at(3);
			string message = tokens.at(4);
			if (this->InChat == true)
			{
				std::cout << source << ":" << message << std::endl;
				break;
			}
			else {
				//chatg.groupName.source.destination.message.offlineG
				Message.append(".");
				Message.append("offlinegG");
				SendString(Message, true);

			}
		}
		if (Message.find("private") != string::npos) {
			//private.groupname.source.destination.message
			mSemaforP = true;
			vector<string> tokens = split(Message, '.');
			string groupName = tokens.at(1);
			string source = tokens.at(2);
			string UserNameDestination = tokens.at(3);
			string message = tokens.at(4);
			if (this->InChat == true)
			{
				std::cout << source << ":" << message << std::endl;
				break;
			}
			else {
				Message.append(".");
				Message.append("offlineP");
				//chatg.groupName.source.destination.message.offlineP
				SendString(Message, true);

				break;
			}
		}

		system("cls");
		std::cout << Message << std::endl; //Display the message to the user
		_getch();
		Sleep(3000);
		break;
	}
	default: //If packet type is not accounted for
		std::cout << "Unrecognized packet: " << _packettype << std::endl; //Display that packet was not found
		break;
	}
	return true;
}


void Client::ClientThread()
{
	Packet PacketType;
	while (true)
	{
		if (!clientptr->GetPacketType(PacketType)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
		if (!clientptr->ProcessPacket(PacketType)) //Process packet (packet type)
			break; //If there is an issue processing the packet, exit this loop
	}
	std::cout << "Lost connection to the server." << std::endl;
	if (clientptr->CloseConnection()) //Try to close socket connection..., If connection socket was closed properly
	{
		std::cout << "Socket to the server was closed successfuly." << std::endl;
	}
	else //If connection socket was not closed properly for some reason from our function
	{
		std::cout << "Socket was not able to be closed." << std::endl;
	}
}

Client::Client(std::string IP, int PORT)
{
	

	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(IP.c_str()); //Address (127.0.0.1) = localhost (this pc)
	addr.sin_port = htons(PORT); //Port 
	addr.sin_family = AF_INET; //IPv4 Socket
	clientptr = this; //Update ptr to the client which will be used by our client thread
	
}


bool Client::Connect()
{
	Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	std::cout << "Connected!" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that will receive any data that the server sends.
	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(Connection) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK) //If socket error is that operation is not performed on a socket (This happens when the socket has already been closed)
			return true; //return true since connection has already been closed

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

