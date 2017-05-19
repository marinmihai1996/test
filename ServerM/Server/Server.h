#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>
#include<deque>
#include"Group.h"
#include"Account.h"
#include"ServerMemory.h"
using namespace std;

enum Packet
{
	P_ChatMessage
};

class Server
{
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();
	void CreateGroup(int ID, std::string name);
	void SingUp(std::string message);
	void LogIn(std::string message);
	void ViewAccountsList();
	void SaveAccount(Account*);
	void RewriteAccountFile();
	void RestoreMemory();
	void SeeInvitations(std::string);
	
	
	Account* getAccount(int ID);
	int GetIdClient(std::string name);
	void InviteClient(std::string);
	void AddMemberInGroup(std::string);

	void GroupChat(std::string);
	void ConnectToGroup(std::string);
	
private:
	void deleteGroup(std::string message);
	void kickMember(std::string message);

	bool sendall(int ID, char * data, int totalbytes);
	bool recvall(int ID, char * data, int totalbytes);

	bool SendInt(int ID, int _int);
	bool GetInt(int ID, int & _int);

	bool SendPacketType(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet & _packettype);

	bool SendString(int ID, std::string & _string);
	bool GetString(int ID, std::string & _string);

	bool ProcessPacket(int ID, Packet _packettype);

	static void ClientHandlerThread(int ID);
	 

private:
	SOCKET Connections[100];
	int IDs = 0;
	//int IDs;
	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;
	
};

static Server * serverptr; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.
