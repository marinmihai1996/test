#include "Server.h"
#include"Utils.h"
#define _SCL_SECURE_NO_WARNINGS



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
	if (newConnection == 0) //If accepting the client connection failed
	{
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}
	else //If client connection properly accepted
	{
		std::cout << "Client Connected!";

		connections[IDs].socket = newConnection; //Set socket in array to be the newest connection before creating the thread to handle this client's socket.
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(IDs), NULL, NULL); //Create Thread to handle this client. The index in the socket array for this thread is the value (i).
		std::string aux = "Connected";
		std::string Id = "ID.";
		Id.append(std::to_string(IDs));
		SendString(IDs, Id);
		SendString(IDs, aux);
		IDs += 1; //Incremenent total # of clients that have connected
		return true;
	}

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
		//Print out data on server details about file that was sent
		std::cout << std::endl << "File sent: " << connections[ID].file.fileName << std::endl;
		std::cout << "File size(bytes): " << connections[ID].file.fileSize << std::endl << std::endl;
	}
	return true;
}
void Server::ClientHandlerThread(int ID) //ID = the index in the SOCKET connections array
{
	Packet PacketType;
	while (true)
	{
		if (!serverptr->GetPacketType(ID, PacketType)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
        if (!serverptr->ProcessPacket(ID, PacketType)) //Process packet (packet type)
			break; //If there is an issue processing the packet, exit this loop
	}
	std::cout << "Lost connection to client ID: " << ID << std::endl;
	closesocket(serverptr->connections[ID].socket);
}

