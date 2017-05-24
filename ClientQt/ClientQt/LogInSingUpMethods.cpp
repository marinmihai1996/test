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

bool Client::LogIn(std::string usename, std::string pass)
{ 

	
	string aux = "login";
	usename.append(".");
	aux.append(".");
	aux.append(usename);
	pass.append(".");
	pass.append(std::to_string(this->ID));
	this->SendString(aux, pass);
	Sleep(2000);

	fflush(NULL);
	if (this->OkSingUp == true)
	{
		return true;

	}
	else return false;
	//else this->ViewMenu1();
}

void Client::SingUp(std::string username, std::string pass)
{

	string aux="createAccount";
	aux.append(username);


	/*string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	path.append(username);
	path.append("/");
	this->FolderPath = path;*/


	aux.append(".");
	pass.append(".");
    pass.append(std::to_string(this->ID)); 
	this->SendString(aux, pass);
	Sleep(2000);

}
