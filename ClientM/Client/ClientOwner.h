#pragma once
#include"Client.h"

class ClientOwner : public Client {
private:
	void SendWelcomeMessage();
	void DeleteGroup();
};