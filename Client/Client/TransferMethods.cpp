#include"Client.h"
#include<fstream>
#include<iostream>
using namespace std;
bool Client::RequestFile(std::string FileName,std::string groupName) {

	// std::string path = ".\\mari\\";
	std::string path = ".\\";
	path.append(this->currentUserName);
	path.append("\\");
	path.append(FileName);
	
	file.outfileStream.open(path, std::ios::binary); //open file to write file to
	file.fileName = FileName; //save file name
	file.bytesWritten = 0; //reset byteswritten to 0 since we are working with a new file
	if (!file.outfileStream.is_open()) //if file failed to open...
	{
		std::cout << "ERROR: Unable to open file: " << FileName << " for writing.\n";
		return false;
	}
	std::cout << "Requesting file from server: " << FileName << std::endl;
	if (!SendPacketType(P_FileTransferRequestFile)) //send file transfer request packet
		return false;
	std::string message = FileName;
	message.append(" ");
	message.append(groupName);
	if (!SendString(message, false)) //send file name
		return false;
	return true;
}


bool Client::UpdateFile(std::string FileName, std::string groupName)
{
	std::string Path = ".\\";
	Path.append(this->currentUserName);
	Path.append("\\");
	Path.append(FileName);
	ifstream toSend(Path);
	if (!toSend) {
		string ErrMsg = "Requested file: " + FileName + " does not exist or was not found.";
		remove(Path.c_str());
		cout << ErrMsg << endl;
		return false;
	}
	if (!SendPacketType(P_FileTransferUpdateFile)) //send file transfer request packet
		return false;
	std::string message = FileName;
	message.append(" ");
	message.append(groupName);
	if (!SendString(message, false)) //send file name
		return false;
	file.infileStream.open(Path, std::ios::binary | std::ios::ate);

	
	file.fileName = FileName; //set file name just so we can print it out after done transferring
	file.fileSize = file.infileStream.tellg(); //Get file size
	file.infileStream.seekg(0); //Set cursor position in file back to offset 0 for when we read file
	file.fileOffset = 0;//path.append(FileName);
	
	if (!HandleSendFile()) //Attempt to send byte buffer from file. If failure...
		return false;

	std::cout << "Uploading file"<< file.fileName <<" to group: " << groupName << std::endl;
	return true;
}


bool Client::HandleSendFile()
{
	if (file.fileOffset >=file.fileSize) //If end of file reached then return true and skip sending any bytes
		return true;
	if (!SendPacketType(P_FileTransferByteBuffer)) //Send packet type for file transfer byte buffer
		return false;

	file.remainingBytes = file.fileSize -file.fileOffset; //calculate remaining bytes
	if (file.remainingBytes > file.buffersize) //if remaining bytes > max byte buffer
	{
		file.infileStream.read(file.buffer, file.buffersize); //read in max buffer size bytes
		if (!Sendint32_t(file.buffersize)) //send int of buffer size
			return false;
		if (!sendall(file.buffer, file.buffersize)) //send bytes for buffer
			return false;
	   file.fileOffset += file.buffersize; //increment fileoffset by # of bytes written
	}
	else
	{
		file.infileStream.read(file.buffer,file.remainingBytes); //read in remaining bytes
		if (!Sendint32_t(file.remainingBytes)) //send int of buffer size
			return false;
		if (!sendall(file.buffer, file.remainingBytes)) //send bytes for buffer
			return false;
		file.fileOffset += file.remainingBytes; //increment fileoffset by # of bytes written
	}

	if (file.fileOffset == file.fileSize) //If we are at end of file
	{
		file.infileStream.close();
		if (!SendPacketType(P_FileTransfer_EndOfFile)) //Send end of file packet
			return false;
		
		std::cout << std::endl << "File sent: " << file.fileName << std::endl;
		std::cout << "File size(bytes): " << file.fileSize << std::endl << std::endl;
	}
	return true;
}