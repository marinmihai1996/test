#include"Client.h"

#include"Utils.h"


bool Client::ProcessPacket(Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage:
	{
		std::string Message;
		if (!GetString(Message))
			return false;
		if (Message.find("Connected") != string::npos) {

			break;
		}
		if (Message.find("ID") != string::npos) {
			vector<string> tokens = split(Message, '.');
			this->ID = stoi(tokens.at(1));
			break;
		}
		if (Message.find("currentUser") != string::npos) {
			vector<string> tokens = split(Message, '.');
			this->currentUserName = tokens.at(1);
			_mkdir(currentUserName.c_str());
			break;
		}
		if (Message.find("You are now online") != string::npos) {
			this->OkSingUp = true;
			std::cout << Message << std::endl;
			break;
		}
		if (Message.find("groupCreated") != string::npos) {
			vector<string> tokens = split(Message, '.');
			string groupName = tokens.at(1);
			std::cout << "The group " << groupName << " is created" << std::endl;
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
			vector<string> tokens = split(Message, '.');
			std::cout << "The members are: " << std::endl;
			for (int i = 1; i < tokens.size(); i++) {
				std::cout << tokens[i];
				std::cout << " ";
			}
			std::cout << endl;
			break;
		}
		if (Message.find("admins") != string::npos) {
			vector<string> tokens = split(Message, '.');
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

			break;
		}
		if (Message.find("invitations.txt") != string::npos) {
			system("cls");
			//Sleep(1000);
			ifstream file(Message);
			if (is_emptyy(file) || !file)
			{
				std::cout << endl;
				std::cout << "You don't have any invitations." << std::endl;

				break;
			}
			else
			{
				ifstream filee;
				filee.open(Message);
				string line;
				while (std::getline(filee, line))
				{
					this->ProcessInvitation(line);
				}
				filee.close();
				// sterg invitatiile din fisier
				std::ofstream ofs;
				ofs.open(Message, std::ofstream::out | std::ofstream::trunc);
				ofs.close();

				break;
			}
		}
		if (Message == "goBack") {
			//system("cls");
			this->ViewMenu2();
			break;
		}
		if (Message.find("groupList") != string::npos) {
			vector<string> tokens = split(Message, '.');
			if (tokens.size() == 1) {
				std::cout << "You are not part of any group " << std::endl;
				break;
			}
			std::cout << "The groups are: " << std::endl;
			for (int i = 1; i < tokens.size(); i++) {
				std::cout << tokens[i];
				std::cout << " ";
			}
			std::cout << endl;
			break;

		}

		if (Message.find("chatg") != string::npos) {
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
				string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
				path.append(UserNameDestination);
				path.append("/");
				path.append(groupName);
				path.append(".txt");
				ofstream OutPut;
				OutPut.open(path, std::ofstream::out | std::ofstream::app);
				OutPut << source;
				OutPut << ":";
				OutPut << message;
				OutPut << "\n";
				OutPut.close();
				break;
			}
		}
		if (Message.find("private") != string::npos) {
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
				string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
				path.append(UserNameDestination);
				path.append("/");
				path.append(groupName);
				path.append(".private.txt");
				ofstream OutPut;
				OutPut.open(path, std::ofstream::out | std::ofstream::app);
				OutPut << source;
				OutPut << ":";
				OutPut << message;
				OutPut << "\n";
				OutPut.close();
				break;
			}
		}


		system("cls");
		std::cout << Message << std::endl; //Display the message to the user
		_getch();
		Sleep(3000);
		break;
	}
	case P_FileTransferByteBuffer:
	{
		int32_t buffersize; //buffer to hold size of buffer to write to file
		if (!Getint32_t(buffersize)) //get size of buffer as integer
			return false;
		if (!recvall(file.buffer, buffersize)) //get buffer and store it in file.buffer
		{
			return false;
		}
		file.outfileStream.write(file.buffer, buffersize); //write buffer from file.buffer to our outfilestream
		file.bytesWritten += buffersize; //increment byteswritten
		std::cout << "Received byte buffer for file transfer of size: " << buffersize << std::endl;
		if (!SendPacketType(P_FileTransferRequestNextBuffer)) //send packet type to request next byte buffer (if one exists)
			return false;
		break;
	}
	case P_FileTransfer_EndOfFile:
	{
		std::cout << "File transfer completed. File received." << std::endl;
		std::cout << "File Name: " << file.fileName << std::endl;
		std::cout << "File Size(bytes): " << file.bytesWritten << std::endl;
		file.bytesWritten = 0;
		file.outfileStream.close();
		break;
	}
	case P_FileTransferRequestNextBuffer:
	{
		if (!HandleSendFile()) //Attempt to send byte buffer from file. If failure...
			return false;
		break;
	}



	default:
		std::cout << "Unrecognized packet: " << _packettype << std::endl;
		break;
	}
	return true;
}