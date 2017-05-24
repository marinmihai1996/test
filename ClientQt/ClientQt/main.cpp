#include "LogIn.h"
#include <QApplication>
#include"Client.h"
int main(int argc, char *argv[])
{
	Client *myClient;
	myClient = new Client("127.0.0.1", 1111);
	if (!myClient->Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}

    QApplication a(argc, argv);
    LogIn w(myClient);
    w.show();

    return a.exec();
}
