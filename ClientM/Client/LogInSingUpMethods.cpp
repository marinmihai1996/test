#include"Client.h"
#include<conio.h>
using namespace std;

string NotShowingPass(string &pass)
{
	pass = "";
	char ch;
	ch = _getch();
	while (ch != 13) {//character 13 is enter
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	std::cout << endl;
	return pass;
}

void Client::LogIn()
{ 
	std::cout << "Username" << std::endl;
	string usename;
	cin >> usename;
	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(usename);
	path.append("/");
	this->FolderPath = path;
	std::cout << "Password" << std::endl;
	string pass;
	NotShowingPass(pass);
	string aux = "login";
	usename.append(".");
	aux.append(".");
	aux.append(usename);
	pass.append(".");
	pass.append(std::to_string(this->ID));
	this->SendString(aux, pass);
	Sleep(2000);
	system("cls");

	fflush(NULL);
	if (this->OkSingUp == true)
	{
		setStatus(off);
		this->ViewMenu2();

	}
	else this->ViewMenu1();
}

void Client::SingUp()
{
	bool ok = false;
	string username;
	string pass;
	while (ok==false)
	{
		std::cout << "Choose an username " << std::endl;
		
		std::cin >> username;
		std::cout << "Choose a password " << std::endl;
		
		NotShowingPass(pass);
		std::cout << "Confirm your password " << std::endl;
		string confirm;
	    NotShowingPass(confirm);
		if (pass.compare(confirm)) {
			std::cout << "The passwod is not the same" << std::endl;
			Sleep(2000);
			system("cls");
			fflush(NULL);
			this->ViewMenu1();
		}
		ok = true;
	}
	string aux="createAccount";
	aux.append(username);


	string path = "C:/Users/Maria/Documents/git/test/ServerM/Server/";
	path.append(username);
	path.append("/");
	this->FolderPath = path;


	aux.append(".");
	pass.append(".");
    pass.append(std::to_string(this->ID)); 
	this->SendString(aux, pass);
	system("pause");
	system("cls");
	fflush(NULL);
	this->OkSingUp = true;
	this->ViewMenu1();
}
