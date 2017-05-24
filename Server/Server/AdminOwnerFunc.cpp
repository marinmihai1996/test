#include"Server.h"
#include"Utils.h"
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
	else numeMembru = a->GetUsername();// ID==numeMembruPtKick

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
		if (option == "kick")
		{ // ii "inchid" consola
			Account*a = mem.getAccount(numeMembru);
			string mes = "goBack";
			SendString(a->GetId(), mes);
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
	if (group->ExistMember(a) == false)
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
	deleteFromFile(groupName, fileName);
	string groupFile = groupName.append(".txt");
	string groupAdminFile = groupName.append(".adminList.txt");
	deleteFile(groupFile);
	deleteFile(groupAdminFile);

}

