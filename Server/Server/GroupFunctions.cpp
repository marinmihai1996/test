#include"Server.h"
#include"Utils.h"


void Server::CreateGroup(int ID, std::string Message) {
	std::string groupName = Message.substr(11, std::string::npos);
	Memory&mem = Memory::GetInstance();
	string ownerName = mem.getAccount(ID)->GetUsername();
	if (mem.ExistsGroup(groupName) == false)
	{
		Group* NewGroup = new Group(groupName, ownerName);
		CreateDirectory(groupName);
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
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
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
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
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
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	path.append(username);
	path.append("/invitations.txt");
	SendString(UserId, path);
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
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	path.append(groupName);
	path.append(".txt");

	file.open(path, std::ifstream::in);
	string FirstLine;
	std::getline(file, FirstLine);
	vector<string> tokenss = split(FirstLine, '.');
	string OwnerName = tokenss.at(0);
	// aici o sa verific si cu vectorul de admini
	string AdminPath = "C:/Users/Maria/Documents/git/test/Server/Server/";
	AdminPath.append(groupName);
	AdminPath.append(".adminList.txt");
	ifstream File(AdminPath);

	if (OwnerName.compare(user->GetUsername()) == 0)
	{
		//user->Rights.MakeOwner();
		string message = "statut.owner";
		SendString(userID, message);

	}
	else if (File) {
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