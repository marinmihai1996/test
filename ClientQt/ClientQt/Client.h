#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline
#include<vector>
#include "FileTransferData.h"
//#include "dialoggroup.h"
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
	std::string mMessageSaved;
	bool mSemafor;
	std::string mMessageSavedP;
	bool mSemaforP;
	std::string getAdmins() { return Admins; };
	std::string getAllGroups() { return Groups; };
	std::string getAllinvits() { return Invitations; };
	enum statut { off, normal, admin, owner };
	std::string getMembers() { return Members; };
	Client(std::string IP, int PORT);
	bool Connect();
	std::string getCale() { return mCaleInv; };
	bool SendString(std::string & _string, bool IncludePacketType = true);
	bool SendString(std::string & _string1, std::string&__string2);
	bool CloseConnection();
	void CreateGroup(std::string groupName);
	void ViewMenu1();
	void ViewMenu2();
	void ViewMenu3(std::string &);

	void ConnectToGroup(std::string groupName);
	void ProcessInvitation(std::string a,std::string s);
	void SeeMemeberList(std::string);
	void SeeAdminList(std::string);
	void RestoreOfflineMessages(std::string groupName,std::string Case,std::string UserName);
	std::string getUsername() { return currentUserName; };
	int ID;
	bool OKforGroup = false;
	bool InChat = false;
	

private: //Private functions
	std::string Mesaj;
	std::string Admins;
	std::string Members;
	std::string MGroups;
	std::string mCaleInv;
	std::string Groups;
	std::string Invitations;
	std::string currentUserName;
	statut Statut;
	void setStatus(statut a) { Statut = a; }
	
	std::string FolderPath;
	bool ProcessPacket(Packet _packettype);
	//static void ClientThread();
	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool Getint32_t(int32_t & _int32_t);
	bool SendPacketType(Packet _packettype);
	bool Sendint32_t(int32_t _int32_t);

public:
	static void ClientThread();
	std::string afiseazaText() { return Mesaj; };
	statut getStatut() { return Statut; }
	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	
	bool GetPacketType(Packet & _packettype);

	void ChatGroup(std::string);
	void PrivateChat(std::string, std::string);
	bool LogIn(std::string nume,std::string parola);
	void SingUp(std::string nume, std::string parola);
	bool HandleSendFile();
	bool UpdateFile(std::string FileName, std::string groupName);
	bool RequestFile(std::string FileName, std::string groupName);
private:
	FileTransferData file;
	//DialogGroup *FereastraGrup;
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
public:bool GetString(std::string & _string);
	bool OkSingUp = false;
		bool GroupCreated = false;
};

static Client * clientptr; //This
