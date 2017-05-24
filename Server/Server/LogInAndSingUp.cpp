#include"Server.h"
#include"Utils.h"



void Server::SingUp(std::string message) {
	std::string accountNameAndPass = message.substr(13, std::string::npos);
	vector<string> tokens = split(accountNameAndPass, '.'); // put the strings in a vector -> delimitator='.'
	string username = tokens.at(0);
	string password = tokens.at(1);
	int ID = std::stoi(tokens.at(2));
	Memory& mem = Memory::GetInstance();

	if (mem.VerifyExistanceAccount(username, password, ID) == 0)
	{
		mem.ChangeIdForSingUp(ID);
		mem.CleanAccountFile();//sterg continutul fisirului
		Account *newAccount = new Account(username, password, ID);
		mem.AddInAccountList(newAccount);
		this->RewriteAccountFile();// rescriu fisierul Accounts.txt
		CreateDirectory(username);

		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string ToSend = "Your account is created!\n";
		SendString(ID, ToSend);


	}
	else if (mem.VerifyExistanceAccount(username, password, ID) == 1)
	{
		string IdMessage = "ID.";
		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message = "This account already exists. Please Login!\n";
		SendString(ID, message);
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
	if (mem.VerifyExistanceAccount(username, password, ID) == 1) {
		// este in memorie
		mem.ChangeIdForLogIn(ID, username); // le schimb in memorie
		mem.CleanAccountFile();
		this->RewriteAccountFile();


		string UsernameToSend = "currentUser.";
		UsernameToSend.append(username);
		SendString(ID, UsernameToSend);
		string IdMessage = "ID.";

		IdMessage.append(std::to_string(ID));
		SendString(ID, IdMessage);
		string message = "You are now online!\n";
		mem.GoOnline(ID);
		this->SendString(ID, message); 
		/*string folderPath = "path.";
		string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
		folderPath.append(path);
		folderPath.append(username);
		path.append("/");
		SendString(ID, folderPath);*/
	}
	else {
		//nu e in memorie
		string message = "You don't have an account!Please Sing up!\n";
		this->SendString(ID, message);
	}
}

