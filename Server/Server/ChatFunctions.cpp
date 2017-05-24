#include"Server.h"
#include"Utils.h"

void Server::PrivateChat(string Message) {

	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(Message, '.');
	string groupName = tokens.at(1);
	Group*group = mem.getGroup(groupName);
	int ID = std::stoi(tokens.at(2));
	string UserToRecive = tokens.at(3);
	string message = tokens.at(4);
	Account*UserDestinaton = mem.getAccount(UserToRecive);
	if (UserDestinaton == NULL)
	{
		string message = "This user do not exists\n";
		SendString(ID, message);
		return;
	}
	if (group->ExistMember(UserDestinaton) == false)
	{
		string message = "This user is not in the group\n";
		SendString(ID, message);
		return;
	}
	Account*Sender = mem.getAccount(ID);
	string mes = "private.";
	mes.append(groupName);
	mes.append(".");
	mes.append(Sender->GetUsername());
	mes.append(".");
	mes.append(UserDestinaton->GetUsername());
	mes.append(".");
	mes.append(message);
	if (!SendString(UserDestinaton->GetId(), mes)) //Send message to connection at index i, if message fails to be sent...
	{
		string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
		path.append(UserDestinaton->GetUsername());
		path.append("/");
		path.append(groupName);
		path.append(".private.txt");
		ofstream OutPut;
		OutPut.open(path, std::ofstream::out | std::ofstream::app);
		OutPut << Sender->GetUsername();
		OutPut << ":";
		OutPut << message;
		OutPut << "\n";
		OutPut.close();
		std::cout << "The user " << UserDestinaton->GetUsername() << "is offline. Gonna see the messages when logs in" << std::endl;

	}

}

void Server::GroupChat(std::string Message)
{
	Memory&mem = Memory::GetInstance();
	std::string MessageAndID = Message.substr(6, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.'); // put the strings in a vector -> delimitator='.'
	string groupName = tokens.at(0);
	int ID = std::stoi(tokens.at(1));
	string message = tokens.at(2);
	Group*group = mem.getGroup(groupName);
	vector<string> GroupMemberList = mem.GetMemberList(group);
	int IdVector[15];
	string SenderName;

	for (int i = 0; i < GroupMemberList.size(); i++)
	{
		Account *a = mem.getAccount(GroupMemberList.at(i));
		IdVector[i] = a->GetId();
		if (IdVector[i] == ID) SenderName = a->GetUsername();
	}

	for (int i = 0; i < GroupMemberList.size(); i++)
	{
		if (IdVector[i] == ID) //If connection is the user who sent the message...
			continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
		string Mes = "chatg.";
		Mes.append(groupName);
		Mes.append(".");
		Mes.append(SenderName);
		Mes.append(".");
		Mes.append(GroupMemberList.at(i));
		Mes.append(".");
		Mes.append(message);

		if (!SendString(IdVector[i], Mes)) //Send message to connection at index i, if message fails to be sent...
		{
			string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
			path.append(GroupMemberList.at(i));
			path.append("/");
			path.append(groupName);
			path.append(".txt");
			ofstream OutPut;
			OutPut.open(path, std::ofstream::out | std::ofstream::app);
			OutPut << SenderName;
			OutPut << ":";
			OutPut << message;
			OutPut << "\n";
			OutPut.close();
			std::cout << "The user " << i << "is offline. Gonna see the messages when logs in" << std::endl;
			//std::cout << "Failed to send message from client ID: " << ID << " to client ID: " << i << std::endl;
		}

	}
}

