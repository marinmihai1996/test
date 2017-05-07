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
			this->ViewMenu();
		}
		
		ok = true;
	}
	
	string aux="createAccount";
	aux.append(username);
	aux.append(".");
	this->SendString(aux, pass);
	std::cout << "Your account in created" << std::endl;
	system("pause");
	system("cls");
	this->ViewMenu();
}
