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
#include "Member.h"
#include"FileTransferData.h"
using namespace std;
class Account;
enum Packet
{
	P_ChatMessage,
	P_FileTransferRequestFile, // when we request a file
	P_FileTransfer_EndOfFile, // to the server to client when the file is completed
	P_FileTransferByteBuffer, // to the server to client
	P_FileTransferRequestNextBuffer,// to the client to the server--to get the next bytebuffer if it exists
	P_FileTransferUpdateFile
};


struct Connection {
	SOCKET socket;
	FileTransferData file;
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
	void MakeAdmin(std::string nume);
	void DowngradeAdmin(std::string nume);
	Account* getAccount(int ID);
	int GetIdClient(std::string name);
	void InviteClient(std::string);
	void QuickAdd(std::string);
	void AddMemberInGroup(std::string);

	void GroupChat(std::string);
	void PrivateChat(std::string);
	void ConnectToGroup(std::string);

	void SeeMemberList(std::string);
	void SeeAdminList(std::string);
	void SeeGroupList(std::string);

private:
	void deleteGroup(std::string message);
	void kickMember(std::string message);

	bool sendall(int ID, char * data, int totalbytes);
	bool recvall(int ID, char * data, int totalbytes);

	
	bool Sendint32_t(int ID, int32_t _int32_t);
	bool Getint32_t(int ID, int32_t & _int32_t);

	bool SendPacketType(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet & _packettype);

	bool SendString(int ID, std::string & _string);
	bool GetString(int ID, std::string & _string);

	bool ProcessPacket(int ID, Packet _packettype);
	bool HandleSendFile(int ID);
	static void ClientHandlerThread(int ID);
	 

private:
	Connection connections[100];
	int IDs = 0;
	//int IDs;
	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;
	
};

static Server * serverptr; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.
