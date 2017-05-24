#include"Server.h"
#include"Utils.h"
bool Server::ProcessPacket(int ID, Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage: //Packet Type: chat message
	{
		std::string Message; //string to store our message we received
		if (!GetString(ID, Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
						  //Next we need to send the message out to each user

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
		std::string RestoreMessageG = "restoreMesG";
		std::string RestoreMessageP = "restoreMesP";

		if (Message.find("offlineG")!=string::npos) {
			this->GroupWriteInFile(Message);
		}

		if (Message.find("offlineP") != string::npos) {
			this->PrivateWriteInFile(Message);
		}
		if (Message.find("restoreMesG") != string::npos) {
			this->RestoreGroupOfflineMessages(Message);
		}
		if (Message.find("restoreMesP") != string::npos) {
			this->RestorePrivateOfflineMessages(Message);
		}

		if (Message.find(Makeadmin) != string::npos) {
			this->MakeAdmin(Message);
		}
		if (Message.find(Downgradeadmin) != string::npos) {
			this->DowngradeAdmin(Message);
		}
		if (Message.find(CreateGroupMessage) != string::npos) {
			CreateGroup(ID, Message);
		}
		if (Message.find(singUp) != string::npos) {
			SingUp(Message);
		}
		if (Message.find(LogIn) != string::npos) {
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
		if (Message.find(JoinGroup) != string::npos) { //nefolosita inca
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
		

		std::cout << "Processed chat message packet from user  " << ID << std::endl;
		break;
	}
	case P_FileTransferRequestFile:
	{
		std::string message; //string to store file name
		if (!GetString(ID, message)) //If issue getting file name
			return false; //Failure to process packet

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
			if (!SendString(ID, ErrMsg)) //Send error msg string to client
				return false;
			//remove(path.c_str());
			return true;
		}
		connections[ID].file.infileStream.open(path, std::ios::binary | std::ios::ate); //Open file to read in binary | ate mode. We use ate so we can use tellg to get file size. We use binary because we need to read bytes as raw data
		if (!connections[ID].file.infileStream.is_open()) //If file is not open? (Error opening file?)
		{
			std::cout << "Client: " << ID << " requested file: " << FileName << ", but that file does not exist." << std::endl;
			std::string ErrMsg = "Requested file: " + FileName + " does not exist or was not found.";
			if (!SendString(ID, ErrMsg)) //Send error msg string to client
				return false;
			if (remove(path.c_str()) == 0) {
				cout << "bine";
			};
			return true;
		}


		connections[ID].file.fileName = FileName; //set file name just so we can print it out after done transferring
		connections[ID].file.fileSize = connections[ID].file.infileStream.tellg(); //Get file size
		connections[ID].file.infileStream.seekg(0); //Set cursor position in file back to offset 0 for when we read file
		connections[ID].file.fileOffset = 0; //Update file offset for knowing when we hit end of file

		if (!HandleSendFile(ID)) //Attempt to send byte buffer from file. If failure...
			return false;

		break;
	}
	case P_FileTransferUpdateFile: {
		std::string message; //string to store file name
		if (!GetString(ID, message)) //If issue getting file name
			return false; //Failure to process packet
		vector<string> tokens = split(message, ' ');
		string FileName = tokens.at(0);
		string groupName = tokens.at(1);
		std::string path = ".\\";
		path.append(groupName);
		path.append("\\");
		path.append(FileName);

		connections[ID].file.outfileStream.open(path, std::ios::binary); //open file to write file to
		connections[ID].file.fileName = FileName; //save file name
		connections[ID].file.bytesWritten = 0; //reset byteswritten to 0 since we are working with a new file
		if (!connections[ID].file.outfileStream.is_open()) //if file failed to open...
		{
			std::cout << "ERROR: Function(Client::RequestFile) - Unable to open file: " << FileName << " for writing.\n";
			return false;
		}

		break;
	}
	case P_FileTransferByteBuffer:
	{
		int32_t buffersize; //buffer to hold size of buffer to write to file
		if (!Getint32_t(ID, buffersize)) //get size of buffer as integer
			return false;
		if (!recvall(ID, connections[ID].file.buffer, buffersize)) //get buffer and store it in file.buffer
		{
			return false;
		}
		connections[ID].file.outfileStream.write(connections[ID].file.buffer, buffersize); //write buffer from file.buffer to our outfilestream
		connections[ID].file.bytesWritten += buffersize; //increment byteswritten
		std::cout << "Received byte buffer for file transfer of size: " << buffersize << std::endl;
		if (!SendPacketType(ID, P_FileTransferRequestNextBuffer)) //send packet type to request next byte buffer (if one exists)
			return false;
		break;
	}

	case P_FileTransferRequestNextBuffer:
	{
		if (!HandleSendFile(ID)) //Attempt to send byte buffer from file. If failure...
			return false;
		break;
	}
	case P_FileTransfer_EndOfFile:
	{
		std::cout << "File transfer completed. File received." << std::endl;
		std::cout << "File Name: " << connections[ID].file.fileName << std::endl;
		std::cout << "File Size(bytes): " << connections[ID].file.bytesWritten << std::endl;
		connections[ID].file.bytesWritten = 0;
		connections[ID].file.outfileStream.close(); //close file after we are done writing file
		break;
	}


	default: //If packet type is not accounted for
	{
		std::cout << "Unrecognized packet: " << _packettype << std::endl; //Display that packet was not found
		break;
	}
	}
	return true;
}