
#include "Server.h"

int main()
{
	Server MyServer(1111); //Create server on port 100
	MyServer.ViewAccountsList();
	for (int i = 0; i < 100; i++) //Up to 100 times...
	{
		MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
	}
	
	system("pause");
	return 0;
}