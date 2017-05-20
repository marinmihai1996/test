#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline

enum Packet
{
	P_ChatMessage

};

class Client
{
public: //Public functions

	enum statut { off, normal, admin, owner };
	
	Client(std::string IP, int PORT);
	bool Connect();

	bool SendString(std::string & _string);
	bool SendString(std::string & _string1, std::string&__string2);
	bool CloseConnection();
	void CreateGroup(std::string groupName);
	void ViewMenu1();
	void ViewMenu2();
	void ViewMenu3(std::string &);

	void ConnectToGroup(std::string groupName);
	void ProcessInvitation(std::string);

	void RestoreOfflineMessages(std::string groupName);
	
	int ID;
	bool OKforGroup = false;
	bool InChat = false;


private: //Private functions

	statut Statut;
	void setStatus(statut a) { Statut = a; }
	statut getStatut() { return Statut; }
	std::string FolderPath;
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);


	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);
	
	void ChatGroup(std::string);
	void LogIn();
	//virtual void DeleteGroup(); //just for ClientOwner
	void SingUp();


private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	bool OkSingUp = false;
};

static Client * clientptr; //This