#include "Server.h"
#define _SCL_SECURE_NO_WARNINGS


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
Server::Server(int PORT, bool BroadcastPublically) //Port = port to broadcast on. BroadcastPublically = false if server is not open to the public (people outside of your router), true = server is open to everyone (assumes that the port is properly forwarded on router settings)
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (BroadcastPublically) //If server is open to public
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else //If server is only for our router
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(PORT); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) //Bind the address to the socket, if we fail to bind the address..
	{
		std::string ErrorMsg = "Failed to bind the address to our listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max connections, if we fail to listen on listening socket...
	{
		std::string ErrorMsg = "Failed to listen on listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	serverptr = this;
	this->RestoreMemory();
	
}

bool Server::ListenForNewConnection()
  {
	SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
	if (newConnection == 0) 
	{
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}
	else 
	{
		std::cout << "Client Connected!";

		connections[IDs].socket = newConnection; //Set socket in array to be the newest connection before creating the thread to handle this client's socket.
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(IDs), NULL, NULL); //Create Thread to handle this client. The index in the socket array for this thread is the value (i).
		std::string aux = "Connected";
		std::string Id = "ID.";
		Id.append(std::to_string(IDs));
		SendString(IDs, Id);
		SendString(IDs, aux);
		IDs += 1; 
		return true;
	}

}


bool Server::ProcessPacket(int ID, Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage: 
	{
		std::string Message; 
		if (!GetString(ID, Message)) 
			return false; 
		
		std::string CreateGroupMessage = "creategroup";
		std::string singUp = "createAccount";
    	std:string LogIn = "login";
		std::string Invitation = "inviteclient";
		std::string QuickAdd = "quickadd";
		std::string ChatGroup = "chatg";
		std::string PrivateChat = "private";
		std::string AccesGroup = "access";
		std::string deleteGroup = "deleteGroup";
		std::string kickMember = "kick";
		std::string JoinGroup = "joingroup";
		std::string SeeInvitation = "seeinvitation";
		std::string SeeMemberList = "seememberlist";
		std::string SeeAdminList = "seeadminlist";
		std::string SeeGroupList = "seegrouplist";
		std::string Makeadmin = "makeadmin";
		std::string Downgradeadmin = "downgrade";
		std::string ExistFile = "FileExists ";


		if (Message.find(Makeadmin)!=string::npos){
			this->MakeAdmin(Message);
		}
		if (Message.find(Downgradeadmin) != string::npos) {
			this->DowngradeAdmin(Message);
		}
		if (Message.find(CreateGroupMessage)!= string::npos){
			CreateGroup(ID, Message);
		}
		if (Message.find(singUp) != string::npos) {
			SingUp(Message);
		}
		if (Message.find(LogIn) != string::npos){
			this->LogIn(Message);
		}
		if (Message.find(Invitation) != string::npos) {
			this->InviteClient(Message);
		}
		if (Message.find(QuickAdd) != string::npos) {
			this->QuickAdd(Message);
		}
		if (Message.find(ChatGroup) != string::npos) {
			this->GroupChat(Message);
		}
		if (Message.find(PrivateChat) != string::npos) {
			this->PrivateChat(Message);
		}
		if (Message.find(AccesGroup) != string::npos) {
			this->ConnectToGroup(Message);
		}
		if (Message.find(deleteGroup) != string::npos) {
			this->deleteGroup(Message);
			
		}
		if (Message.find(kickMember) != string::npos) {
			this->kickMember(Message);
		}

		if (Message.find(SeeInvitation) != string::npos) {
			this->SeeInvitations(Message);
		}
		if (Message.find(JoinGroup) != string::npos) {
			this->AddMemberInGroup(Message);
		}
		if (Message.find(SeeMemberList) != string::npos) {
			this->SeeMemberList(Message);
		}
		if (Message.find(SeeAdminList) != string::npos) {
			this->SeeAdminList(Message);
		}
		if (Message.find(SeeGroupList) != string::npos) {
			this->SeeGroupList(Message);
		}
		if (Message.find(ExistFile) != string::npos) {
			vector<string> tokens = split(Message, ' ');
			int ID = stoi(tokens.at(1));
			string groupName = tokens.at(2);
			string message = "confirmation";
			SendString(ID, message);
		}

		std::cout << "Processed chat message packet from user  " << ID << std::endl;
		break;
	}
	case P_FileTransferRequestFile:
	{
		std::string message; 
		if (!GetString(ID, message)) 
			return false; 
		if (message.find(" ") == string::npos)
		{
			std::string ErrMsg = "Requested file does not exist or was not found.";
			if (!SendString(ID, ErrMsg)) 
				return false;
			return false;
		}
		vector<string> tokens = split(message, ' ');
		string FileName = tokens.at(0);
		string groupName = tokens.at(1);
		std::string path = ".\\";
		path.append(groupName);
		path.append("\\");

		path.append(FileName);
		ifstream toSend(path);
		if (!toSend) {
			std::cout << "Client: " << ID << " requested file: " << FileName << ", but that file does not exist." << std::endl;
			std::string ErrMsg = "Requested file: " + FileName + " does not exist or was not found.";
			if (!SendString(ID, ErrMsg)) 
				return false;
			return true;
		}
		connections[ID].file.infileStream.open(path, std::ios::binary | std::ios::ate); 
		if (!connections[ID].file.infileStream.is_open()) 
		{
			std::cout << "Client: " << ID << " requested file: " << FileName << ", but that file does not exist." << std::endl;
			std::string ErrMsg = "Requested file: " + FileName + " does not exist or was not found.";
			if (!SendString(ID, ErrMsg)) 
				return false;
			return true;
		}
	
		
		connections[ID].file.fileName = FileName; 
		connections[ID].file.fileSize = connections[ID].file.infileStream.tellg(); //Get file size
		connections[ID].file.infileStream.seekg(0); //Set cursor position in file back to offset 0 for when we read file
		connections[ID].file.fileOffset = 0; //Update file offset for knowing when we hit end of file

		if (!HandleSendFile(ID)) //Attempt to send byte buffer from file. If failure...
			return false;
		
		break;
	}

	case P_FileTransferUpdateFile: {
		std::string message;
		if (!GetString(ID, message))
			return false; 
		vector<string> tokens = split(message, ' ');
		string FileName = tokens.at(0);
		string groupName = tokens.at(1);
		std::string path = ".\\";
		path.append(groupName);
		path.append("\\");
		path.append(FileName);

		connections[ID].file.outfileStream.open(path, std::ios::binary); 
		connections[ID].file.fileName = FileName; 
		connections[ID].file.bytesWritten = 0; 
		if (!connections[ID].file.outfileStream.is_open()) 
		{
			std::cout << "ERROR: Function(Client::RequestFile) - Unable to open file: " << FileName << " for writing.\n";
			return false;
		}

		break;
	}
	case P_FileTransferByteBuffer:
	{
		int32_t buffersize;
		if (!Getint32_t(ID,buffersize)) //get size of buffer as integer
			return false;
		if (!recvall(ID,connections[ID].file.buffer, buffersize)) //get buffer and store it in file.buffer
		{
			return false;
		}
		connections[ID].file.outfileStream.write(connections[ID].file.buffer, buffersize); //write buffer from file.buffer to our outfilestream
		connections[ID].file.bytesWritten += buffersize; //increment byteswritten
		std::cout << "Received byte buffer for file transfer of size: " << buffersize << std::endl;
		if (!SendPacketType(ID,P_FileTransferRequestNextBuffer)) //send packet type to request next byte buffer (if one exists)
			return false;
		break;
	}

	case P_FileTransferRequestNextBuffer:
	{
		if (!HandleSendFile(ID)) 
			return false;
		break;
	}
	case P_FileTransfer_EndOfFile:
	{
		std::cout << "File transfer completed. File received." << std::endl;
		std::cout << "File Name: " << connections[ID].file.fileName << std::endl;
		std::cout << "File Size(bytes): " << connections[ID].file.bytesWritten << std::endl;
		connections[ID].file.bytesWritten = 0;
		connections[ID].file.outfileStream.close(); 
		break;
	}

	default: 
	{
		std::cout << "Unrecognized packet: " << _packettype << std::endl; 
		break;
	}
	}  
	return true;
}
bool Server::HandleSendFile(int ID)
{

	if (connections[ID].file.fileOffset >= connections[ID].file.fileSize) //If end of file reached then return true and skip sending any bytes
		return true;
	if (!SendPacketType(ID, P_FileTransferByteBuffer)) //Send packet type for file transfer byte buffer
		return false;

	connections[ID].file.remainingBytes = connections[ID].file.fileSize - connections[ID].file.fileOffset; //calculate remaining bytes
	if (connections[ID].file.remainingBytes > connections[ID].file.buffersize) //if remaining bytes > max byte buffer
	{
		connections[ID].file.infileStream.read(connections[ID].file.buffer, connections[ID].file.buffersize); //read in max buffer size bytes
		if (!Sendint32_t(ID, connections[ID].file.buffersize)) //send int of buffer size
			return false;
		if (!sendall(ID, connections[ID].file.buffer, connections[ID].file.buffersize)) //send bytes for buffer
			return false;
		connections[ID].file.fileOffset += connections[ID].file.buffersize; //increment fileoffset by # of bytes written
	}
	else
	{
		connections[ID].file.infileStream.read(connections[ID].file.buffer, connections[ID].file.remainingBytes); //read in remaining bytes
		if (!Sendint32_t(ID, connections[ID].file.remainingBytes)) //send int of buffer size
			return false;
		if (!sendall(ID, connections[ID].file.buffer, connections[ID].file.remainingBytes)) //send bytes for buffer
			return false;
		connections[ID].file.fileOffset += connections[ID].file.remainingBytes; //increment fileoffset by # of bytes written
	}

	if (connections[ID].file.fileOffset == connections[ID].file.fileSize) //If we are at end of file
	{
		connections[ID].file.infileStream.close();
		if (!SendPacketType(ID, P_FileTransfer_EndOfFile)) //Send end of file packet
			return false;
		
		std::cout << std::endl << "File sent: " << connections[ID].file.fileName << std::endl;
		std::cout << "File size(bytes): " << connections[ID].file.fileSize << std::endl << std::endl;
	}
	return true;
}
void Server::ClientHandlerThread(int ID) 
{
	Packet PacketType;
	while (true)
	{
		if (!serverptr->GetPacketType(ID, PacketType)) 
			break; 
        if (!serverptr->ProcessPacket(ID, PacketType)) 
			break; 
	}
	std::cout << "Lost connection to client ID: " << ID << std::endl;
	closesocket(serverptr->connections[ID].socket);
}

