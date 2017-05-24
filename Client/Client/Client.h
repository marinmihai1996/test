#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") 
#include <WinSock2.h> 
#include <string> 
#include <iostream>
#include "FileTransferData.h"
enum Packet
{
	P_ChatMessage,
	P_FileTransferRequestFile, // when we request a file
	P_FileTransfer_EndOfFile, // to the server to client when the file is completed
	P_FileTransferByteBuffer, // to the server to client
	P_FileTransferRequestNextBuffer, // to the client to the server--to get the next bytebuffer if it exists
	P_FileTransferUpdateFile
};

class Client
{
public: //Public functions

	enum statut { off, normal, admin, owner };
	
	Client(std::string IP, int PORT);
	bool Connect();
	bool RequestFile(std::string filename,std::string groupName);
	bool UpdateFile(std::string FileName, std::string groupName);
	bool HandleSendFile();

	bool SendString(std::string & _string,bool IncludePacketType=true);
	bool SendString(std::string & _string1, std::string&__string2);
	bool CloseConnection();
	void CreateGroup(std::string groupName);
	void ViewMenu1();
	void ViewMenu2();
	void ViewMenu3(std::string &);

	void ConnectToGroup(std::string groupName);
	void ProcessInvitation(std::string);
	void SeeMemeberList(std::string);
	void SeeAdminList(std::string);
	void RestoreOfflineMessages(std::string groupName,std::string Case,std::string UserName);
	
	int ID;
	bool OKforGroup = false;
	bool InChat = false;
	std::string currentUserName;
	
	

private: //Private functions

	statut Statut;
	void setStatus(statut a) { Statut = a; }
	statut getStatut() { return Statut; }
	std::string FolderPath;
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();

	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool Sendint32_t(int32_t _int32_t);
	bool SendPacketType(Packet _packettype);


	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	bool Getint32_t(int32_t & _int32_t);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);
	
	void ChatGroup(std::string);
	void PrivateChat(std::string, std::string);
	void LogIn();
	void SingUp();


private:
	FileTransferData file;
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	bool OkSingUp = false;
};

static Client * clientptr; //This