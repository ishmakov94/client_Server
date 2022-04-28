#include "../common/socket/Socket.hpp"
#include "../common/Constants.hpp"
#include "../common/Logic.hpp"
#include "clientStorage/ClientStorageManager.hpp"
#include <iostream>
#include <cstring>
#include <thread>

class Server
{
public:
	Server() = default;
	~Server();
	Server(uint16_t portTcp, uint16_t portUdp);
	void run();
private:
	Socket* socketTcp;
	Socket* socketUdp;
	void runClientStorageManager(bool& status);
	void runTcp(bool& status, ClientStorageManager* clientStorageManager);
	void runUdp(bool& status);
	void runCmd(bool& status);
	void printCmdHelp();
};