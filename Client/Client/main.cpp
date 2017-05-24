#include "Client.h"


int main()
{
	Client myClient("127.0.0.1", 1111); //Create client to localhost ("127.0.0.1") on port 1111

	if (!myClient.Connect())
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	myClient.ViewMenu1(); 
	
	
	return 0;
}

   