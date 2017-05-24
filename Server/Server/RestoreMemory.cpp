#include"ServerMemory.h"
#include"Utils.h"


void Server::RestoreMemory()
{
	Memory& mem = Memory::GetInstance();
	mem.RestoreAccountList();
	mem.RestoreGroupsList();
}

void Memory::RestoreAccountList() {
	LogAccounts& Log = LogAccounts::GetInstance();
	string line;
	ifstream myfile("C:/Users/Maria/Documents/git/test/Server/Server/Accounts.txt");
	if (myfile.good()) {
		while (getline(myfile, line)) {  // same as: while (getline( myfile, line ).good())

			vector<string>tokens = split(line, ' ');
			string username = tokens.at(0);
			string password = tokens.at(1);
			int ID = std::stoi(tokens.at(2));
			Account *newAccount = new Account(username, password, ID);
			this->AddInAccountList(newAccount);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
};

void Memory::RestoreAdminList(Group*group) {
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	string name = group->GetGroupName();
	path.append(name);
	path.append(".adminList.txt");
	ifstream file(path);
	if (is_emptyy(file) || !file) return;
	ifstream filee;
	filee.open(path);
	string line;
	while (std::getline(filee, line))
	{
		Account *a = this->getAccount(line);

		this->AddAdmin(group, a);
	}


}
void Memory::RestoreGroupsList() {

	LogGroups& Log = LogGroups::GetInstance();
	string line;
	ifstream myfile("C:/Users/Maria/Documents/git/test/Server/Server/Groups.txt");
	if (myfile.good()) {
		while (getline(myfile, line)) {  // same as: while (getline( myfile, line ).good())
			vector<string>tokens = split(line, ' ');
			string groupName = tokens.at(0);
			string ownerName = tokens.at(1);
			Group*group = new Group(groupName, ownerName);
			this->AddInGroupList(group);

		}
		myfile.close();
	}
	else cout << "This server doesn't have any groups yet!\n";

};
void Memory::RestoreGroupAccountsList(Group*group)
{
	string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	std::string groupName = group->GetGroupName();
	path.append(groupName);
	path.append(".txt");
	ifstream InFile(path); // deschid fisierul grupului unde se afla membrii
	string line;
	if (InFile.good()) {
		while (getline(InFile, line)) {
			string username = line;;
			Account *account = this->getAccount(username);
			group->addAccount(account);
		}
	}
}