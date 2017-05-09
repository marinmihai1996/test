#include "Client.h"
using namespace std;

//unsigned int Client::NextID = 0;
bool Client::ProcessPacket(Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage: //If packet is a chat message packet
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		std::cout << Message << std::endl; //Display the message to the user
		break;
	}
	case P_Int:
	{
		int IntMessage;
		if (!GetInt(IntMessage)) return false;
		//std::cout << IntMessage << std::endl;
		if (IntMessage < 1000) {
			this->ID = IntMessage;
			std::cout << "Connected to the server!" << std::endl;
			std::cout << "Welcome to the M&M GroupChat!" << std::endl;
			std::cout << "Your ID = " << IntMessage << endl;
			//this->ViewMenu1();
			break;
		}
		if (IntMessage == 1000) {
			std::cout << "Your account is created!\n";
			std::cout << "Log In\n";
			LogIn();
			break;
		}
		if (IntMessage == 1001) {
			std::cout << "This account already exists. Please Login!\n";
			break;
		}
		if (IntMessage == 1002) {
			std::cout << "This username is taken.Please choose another one!\n";
			break;
		}
		if (IntMessage == 1003) {
			std::cout << "You are now online!\n";
			break;
		}
		if (IntMessage == 1004) {
			std::cout << "You don't have an account!Please Sing up!\n";
			break;
		   }
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

	addr.sin_addr.s_addr = inet_addr(IP.c_str()); //Address 127.0.0.1 = localhost (This pc)
	addr.sin_port = htons(PORT); //Port to connect on
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
void Client::CreateGroup(std::string groupName)
{
	std::string CreateGroupMessage = "creategroup";
	std::string ErrorMessage = "Failed to create a group";
	if (!this->SendString(CreateGroupMessage, groupName))
		SendString(ErrorMessage);

	Sleep(10);

}
