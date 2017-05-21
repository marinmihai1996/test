#ifndef _header_4344
#define _header_4334
#include<vector>
#include<direct.h>
#include"Server.h"
#include"Account.h"
#include"LogAccounts.h"
#include"LogGroups.h"
#include<fstream>
#include "Admin.h"
#include "Owner.h"
#include "Member.h"
using namespace std;
ofstream write;



bool is_emptyy(std::ifstream& pFile);

void CreateDirectory(string name)
{
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(name);
	_mkdir(path.c_str());
}
void deleteFile(string FileName)
{
	char * writable = new char[FileName.size() + 1];
	std::copy(FileName.begin(), FileName.end(), writable);
	writable[FileName.size()] = '\0'; // don't forget the terminatination
	remove(writable);
	delete[] writable;
}
bool deleteFromFile(string name, string FileName) {
	bool exist = false;
	vector<string> BackUpVector;
	string file = FileName.append(".txt");
	string line;
	ifstream InFile(file);
	if (InFile.good()) {
		while (getline(InFile, line)) {
			if (line == name||line.find(name)!=string::npos) exist = true;
			else  BackUpVector.push_back(line);
		}
	}
	if (exist == true)
	{
		InFile.close();
		std::ofstream ofs;
		ofs.open(file, std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream OutPut;
		OutPut.open(file, std::ofstream::out | std::ofstream::app);
		for (int i = 0; i < BackUpVector.size(); i++) {
			OutPut << BackUpVector[i];
			OutPut << "\n";
		}
	}
	return exist;
}

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
Account* Server::getAccount(int ID)
{
	Memory& mem = Memory::GetInstance();
	return mem.getAccount(ID);
}

int Server::GetIdClient(std::string name)
{
	Memory& mem = Memory::GetInstance();
	return mem.GetId(name);
}

void Server::CreateGroup(int ID,std::string Message){ 
	std::string groupName = Message.substr(11, std::string::npos);
	Memory&mem = Memory::GetInstance();
	string ownerName = mem.getAccount(ID)->GetUsername();
	if (mem.ExistsGroup(groupName) == false)
	{
		Group* NewGroup = new Group(groupName, ownerName);
		LogGroups&groups = LogGroups::GetInstance();
		string auxx;
		auxx.append(groupName);
		auxx.append(" ");
		auxx.append(ownerName);
		auxx.append("\n");
		groups.Write(auxx);

		NewGroup->addAccount(getAccount(ID)); // il adaug in memorie
		groupName.append(".txt"); // ii creez fisierul
		vector<string> tokens = split(groupName, '.');
		string name = tokens.at(0);
		ofstream OutPut;
		
		Account*aux = getAccount(ID); // scriu in fisier owner-ul
		OutPut.open(groupName, std::ofstream::out | std::ofstream::app);
		OutPut << aux->GetUsername();
		OutPut << "\n";
		OutPut.close();
	
		mem.AddInGroupList(NewGroup);
		string message = "groupCreated.";
		message.append(groupName);
		SendString(ID, message);
	}
	else {
		string message = "This name is taken.Choose another one";
		SendString(ID, message);
	}
}
void Server::RewriteAccountFile()
{
	Memory& mem = Memory::GetInstance();
	for (int i = 0; i < mem.GetAccountListSize(); i++) {
		this->SaveAccount(mem.getAccountForIndex(i));
	}
}

void Server::SingUp(std::string message) {
	std::string accountNameAndPass = message.substr(13, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password= tokens.at(1);
	int ID = std::stoi(tokens.at(2)); 
	Memory& mem = Memory::GetInstance();

	if (mem.VerifyExistanceAccount(username, password,ID) == 0)
	{
	    mem.ChangeIdForSingUp(ID);
		mem.CleanAccountFile();//sterg continutul fisirului
		Account *newAccount = new Account(username, password,ID);
		mem.AddInAccountList(newAccount);
		this->RewriteAccountFile();// rescriu fisierul Accounts.txt
		CreateDirectory(username);
		
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string ToSend = "Your account is created!\n";
		SendString(ID, ToSend);
		
	}
	else if (mem.VerifyExistanceAccount(username, password,ID) == 1)
	{
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message = "This account already exists. Please Login!\n";
		SendString(ID,message);
	}
	else {
	
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message = "This username is taken.Please choose another one!\n";
		SendString(ID, message);
	}
}
void Server::LogIn(std::string message) {
	
	std::string accountNameAndPass = message.substr(6, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password = tokens.at(1);
	int ID = stoi(tokens.at(2));
	
	Memory& mem = Memory::GetInstance();
	if (mem.VerifyExistanceAccount(username, password,ID) == 1) {
		// este in memorie
		mem.ChangeIdForLogIn(ID,username); // le schimb in memorie
		mem.CleanAccountFile();
		this->RewriteAccountFile();

		string IdMessage = "ID.";

		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message= "You are now online!\n";
		mem.GoOnline(ID);
		this->SendString(ID, message);
	}
	else {
		//nu e in memorie
		string message = "You don't have an account!Please Sing up!\n";
		this->SendString(ID, message);
	}
}


void  Server::SaveAccount(Account *a){

	LogClass&MyLogClass = LogClass::GetInstance();
	string aux;
	aux.append(a->GetUsername());
	aux.append(" ");
	aux.append(a->GetPassword());
	aux.append(" ");
	aux.append(std::to_string(a->GetId()));
	aux.append("\n");
	MyLogClass.Write(aux);
	
}


void Server::RestoreMemory()
{
	Memory& mem = Memory::GetInstance();
	mem.RestoreAccountList();
	mem.RestoreGroupsList(); 
}


void Server::InviteClient(string message)
{
	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(message, '.'); // put the strings in a vector -> delimitator='.'
	int ID = stoi(tokens.at(1));
	string clientName = tokens.at(2);
	Account *account = mem.getAccount(clientName);
	if (account == NULL) {
		string errorMessage = "This user do not exists!!\n";
		SendString(ID, errorMessage);
		return;
	}
	string GroupName = tokens.at(3);
	Group*group = mem.getGroup(GroupName);
	if (group->ExistMember(account) == true) {
		string errorMessage = "This is already a member\n";
		SendString(ID, errorMessage);
		return;
	}
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(clientName.c_str());
	path.append("/");
	path.append("invitations.txt");
	ifstream myfile(path);
	string line;
	if (myfile)
	{
		if (myfile.good() && !is_emptyy(myfile)) {
			while (getline(myfile, line)) {
				if (line == GroupName)
				{
					string errorMessage = "This member is already invited\n";
					SendString(ID, errorMessage);
					break;
				}
			}

			myfile.close();
			return;
		}
	}
	std::ofstream ofs;
	ofs.open(path, std::ofstream::out | std::ofstream::app);
	ofs << GroupName;
	ofs << "\n";
	ofs.close();
}
void Server::QuickAdd(string message) {
	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(message, '.');
	int ID = stoi(tokens.at(1));
	string groupName = tokens.at(2);
	string userName = tokens.at(3);
	Account*account = mem.getAccount(userName);
	if (account == NULL) {
		string errorMessage = "This user do not exists!!\n";
		SendString(ID, errorMessage);
		return;
	}
	Group*group = mem.getGroup(groupName);
	if (group->ExistMember(account) == true) {
		string errorMessage = "This is already a member\n";
		SendString(ID, errorMessage);
		return;
	}
	group->addAccount(account);
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(groupName);
	path.append(".txt");
	std::ofstream ofs;
	ofs.open(path, std::ofstream::out | std::ofstream::app);
	ofs << userName;
	ofs << "\n";
	ofs.close();


}


void Server::AddMemberInGroup(string message)
{
	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(message, '.');
	string group = tokens.at(1);
	int userID = stoi(tokens.at(2));
	Group*Group = mem.getGroup(group);
	Account *account = mem.getAccount(userID);
	if (account == NULL) {
		string errorMessage = "This user do not exists!!\n";
		SendString(userID, errorMessage);
		return;
	}
	Group->addAccount(account);
	ofstream OutPut;
	group.append(".txt");
	OutPut.open(group, std::ofstream::out | std::ofstream::app); 
	OutPut << account->GetUsername();
	OutPut << "\n";
	OutPut.close();

}

void Server::SeeInvitations(string message)
{
	vector<string> tokens = split(message, '.');
	int UserId = stoi(tokens.at(1));
	Memory&mem = Memory::GetInstance();
	Account*acc = mem.getAccount(UserId);
	string username = acc->GetUsername();
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(username);
	path.append("/invitations.txt");
	SendString(UserId, path);
}
void Server::PrivateChat(string Message) {

	Memory&mem = Memory::GetInstance();
	vector<string> tokens = split(Message, '.');
	string groupName = tokens.at(1);
	Group*group = mem.getGroup(groupName);
	int ID = std::stoi(tokens.at(2));
	string UserToRecive=tokens.at(3);
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
		string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
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
	vector<string> tokens = split(MessageAndID,'.'); // put the strings in a vector -> delimitator='.'
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
			string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
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

void Server::ConnectToGroup(std::string Message) {

	std::string groupNameAndID = Message.substr(7, std::string::npos);
	Memory& mem = Memory::GetInstance();
	vector<string> tokens = split(groupNameAndID, '.');
	string groupName = tokens.at(0);
	int userID = stoi(tokens.at(1));
	Account*user = mem.getAccount(userID);
	Group*group = mem.getGroup(groupName);
	if (group == NULL) {
		string message = "This group do not exists!\n";
		SendString(userID, message);
		return;
	}
	mem.RestoreAdminList(group);
	std::ifstream file;
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(groupName);
	path.append(".txt");

	file.open(path, std::ifstream::in);
	string FirstLine;
	std::getline(file, FirstLine);
	vector<string> tokenss = split(FirstLine, '.');
	string OwnerName = tokenss.at(0);
	// aici o sa verific si cu vectorul de admini
	string AdminPath = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	AdminPath.append(groupName);
	AdminPath.append(".adminList.txt");
	ifstream File(AdminPath);

	if (OwnerName.compare(user->GetUsername()) == 0)
	{
		//user->Rights.MakeOwner();
		string message = "statut.owner";
		SendString(userID, message);

	}
	else if(File){
		if (!is_emptyy(File)) {
			ifstream filee;
			filee.open(AdminPath);
			string line;
			while (std::getline(filee, line))
			{
				if (line == user->GetUsername()) {
					string message = "statut.admin";
					SendString(userID, message);
				}
			}
		}
	}
	else
	{
		//user->Rights.OnlyMember();
		string message = "statut.member";
		SendString(userID, message);
	}

	//verific daca grupul exista
	if (mem.ExistsGroup(groupName) == true) {
		Group *group = mem.getGroup(groupName);
		//acum verific daca user-ul face parte din grup
		if (group->ExistMember(user) == true) {
			string message = "InGroup.";
			message.append(groupName);
			SendString(userID, message);
		}
		else {
			string message = "You are not a member of this group!";
			SendString(userID, message);
		}
	}
	else {
		string message = "This group do not exists!";
		SendString(userID, message);
	}

}

void Server::deleteGroup(std::string Message)
 {
	//Message= deletgroup.ID.numegrup
	//std::string MessageAndID = Message.substr(10, std::string::npos);
	vector<string> tokens = split(Message, '.');
	int userID = stoi(tokens.at(1));
	string groupName = tokens.at(2);
	Memory&mem = Memory::GetInstance();
	Group*Group = mem.getGroup(groupName);
	if (Group == NULL) {
		string message = "This group do not exists!";
		SendString(userID, message);
		return;
	}
	mem.deleteGroup(Group);
	string fileName = "Groups";
	deleteFromFile(groupName,fileName);
	string groupFile = groupName.append(".txt");
	string groupAdminFile = groupName.append(".adminList.txt");
	deleteFile(groupFile);
	deleteFile(groupAdminFile);
	
	}
	
	


void Server::kickMember(std::string Message)
{
	//Message= kickmember.id.numegrup.numemembrupentrukick.kick 
	Memory&mem = Memory::GetInstance();
	std::string MessageAndID = Message.substr(11, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	string option = tokens.at(3);
	string numeMembru;
	int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	Account*a = mem.getAccount(ID);
	if (option == "kick")
	{
	   numeMembru = tokens.at(2);
	}
	else numeMembru = a->GetUsername();

	Group*group = mem.getGroup(numeGrup);
	if (option == "leave") goto et;
	// sa mai fac si daca e owner si vrea sa plece!!! 
	if (numeMembru == group->GetGroupOwnerName()) {
		string message = "That is the owner of the group.You don't have the rights to do this";
		SendString(ID, message);
		return;
	}
	if (a->GetUsername() == numeMembru) {
		string message = "That is you! :)";
		SendString(ID, message);
		return;
	}
et:
	if (group->kickMember(numeMembru) == true)
	{
		deleteFromFile(numeMembru, numeGrup);
		if (group->kickAdmin(numeMembru) == true)
		{
			string adminFile = ".adminList";
			numeGrup.append(adminFile);
			deleteFromFile(numeMembru, numeGrup);

		}
	}
}
	



void Server::MakeAdmin(std::string Message)
{
	///makeadmin.id.numegrup.numemembru

	std::string MessageAndID = Message.substr(10, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	string numeMembru = tokens.at(2);

	Memory&mem = Memory::GetInstance();
				Group*group = mem.getGroup(numeGrup);
				Account *account = mem.getAccount(numeMembru, numeGrup);
				if (account == NULL) {
					string errorMessage = "This user do not exists!!\n";
					SendString(ID, errorMessage);
					return;
				}
				if (numeMembru == group->GetGroupOwnerName()) {
					string errorMessage = "This is the owner of the group\n";
					SendString(ID, errorMessage);
					return;
				}
				if (group->ExistAdmin(account) == true) {
					string errorMessage = "This is already an admin\n";
					SendString(ID, errorMessage);
					return;
				}
				string stat = "statut.admin";
				int id = account->GetId();
				mem.AddAdmin(group, account);
				SendString(id, stat);
				std::string name = ".adminList";
				numeGrup.append(name);
				numeGrup.append(".txt");

				ofstream OutPut;
				
				OutPut.open(numeGrup, std::ofstream::out | std::ofstream::app);
				OutPut << account->GetUsername();
				OutPut << "\n";
				OutPut.close();

}
		
void Server::DowngradeAdmin(std::string Message)
{
	///downgradeadmin.id.numegrup.numeadmin

	std::string MessageAndID = Message.substr(15, std::string::npos);
	vector<string> tokens = split(MessageAndID, '.');
	int ID = std::stoi(tokens.at(0));
	string numeGrup = tokens.at(1);
	string numeMembru = tokens.at(2);
	Memory&mem = Memory::GetInstance();
	Account*a = mem.getAccount(numeMembru);
	if (a == NULL) {
		string message = "The accout do not exists";
		SendString(ID, message);
		return;
	}
	Group*group = mem.getGroup(numeGrup);
	if (group->ExistMember(a)==false)
	{
		string message = "The accout is not a member  of this group";
		SendString(ID, message);
		return;
	}
	if (group->ExistAdmin(a) == false)
	{
		string message = "The accout is not an admin of this group";
		SendString(ID, message);
		return;
	}
	group->kickAdmin(numeMembru);
	string file = ".adminList";
	numeGrup.append(file);
	deleteFromFile(numeMembru, numeGrup);
	string s = "Admin downgraded!!\n";
	SendString(ID, s);
	
}
	


void Server::SeeMemberList(std::string message)
{
	Memory& mem = Memory::GetInstance();
	vector<string> MemberList;
	vector<string> tokens = split(message, '.'); // put the strings in a vector -> delimitator='.'
	string groupName = tokens.at(1);
	int ID = stoi(tokens.at(2));
	
	MemberList = mem.GetMemberList(groupName);
	string Message = "members";
	for (int i = 0; i < MemberList.size(); i++) {
		Message.append(".");
		Message.append(MemberList.at(i));
	}
	SendString(ID, Message);	
}
void Server::SeeAdminList(std::string message)
{
	Memory& mem = Memory::GetInstance();
	vector<string> AdminList;
	vector<string> tokens = split(message, '.'); // put the strings in a vector -> delimitator='.'
	string groupName = tokens.at(1);
	int ID = stoi(tokens.at(2));

	AdminList = mem.GetAdminList(groupName);
	string Message = "admins";
	for (int i = 0; i < AdminList.size(); i++) {
		Message.append(".");
		Message.append(AdminList.at(i));
	}
	SendString(ID, Message);
}
void Server::SeeGroupList(std::string message) {
	Memory& mem = Memory::GetInstance();
	vector<string> GroupList;
	vector<string> tokens = split(message, '.');
	int ID = stoi(tokens.at(1));
	Account*a = mem.getAccount(ID);
	GroupList = mem.GetGroupList(a);
	string Message = "groupList";
	for (int i = 0; i < GroupList.size(); i++) {
		Message.append(".");
		Message.append(GroupList[i]);
	}
	SendString(ID, Message);

}



void Server::ViewAccountsList()
{
	//std::cout << " The Accounts are: " << std::endl;
	Memory& mem = Memory::GetInstance();
	mem.ViewAccountsList();
}
#endif