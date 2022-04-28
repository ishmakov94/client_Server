#include "Server.hpp"

Server::Server(uint16_t portTcp, uint16_t portUdp)
{
	socketTcp = new Socket(portTcp, Proto::TCP);
	socketUdp = new Socket(portUdp, Proto::UDP);
	socketTcp->_bind();
	socketUdp->_bind();
}

Server::~Server()
{
	delete socketTcp;
	delete socketUdp;
}

void Server::run()
{
	bool status = true;
	ClientStorageManager* clientStorageManager = new ClientStorageManager();
	std::thread storageManagerThread(&ClientStorageManager::run, clientStorageManager, std::ref(status));
	std::thread tcpTread(&Server::runTcp, this, std::ref(status), std::ref(clientStorageManager));
	std::thread udpThread(&Server::runUdp, this, std::ref(status));
	std::thread cmdThread(&Server::runCmd, this, std::ref(status));
	cmdThread.join();
	storageManagerThread.join();
	tcpTread.join();
	udpThread.join();
	delete clientStorageManager;
}

void Server::runTcp(bool& status, ClientStorageManager* clientStorageManager)
{
	while(status)
	{
		sleep(2);
		int fd = -1;
		socketTcp->listenAndAccept(fd);
		if(fd != -1)
		{
			clientStorageManager->addClient(fd);
		}
	}
}
void Server::runUdp(bool& status)
{
	char* buffer = new char[BUFFER_SIZE];
	std::string w_buf {};
	while(status)
	{
		sockaddr_in cliaddr {0};
		socklen_t len = sizeof(cliaddr);
		memset(buffer, 0, BUFFER_SIZE);
		ssize_t nread = recvfrom(socketUdp->getSocketFd(), buffer, BUFFER_SIZE, MSG_WAITALL,
                 (sockaddr *) &cliaddr, &len);
		auto sum = findSum(buffer, nread);
		if(sum.first)
		{
			w_buf = std::to_string(sum.second);
			sendto(socketUdp->getSocketFd(), w_buf.c_str(), w_buf.length(), MSG_CONFIRM,
               		(const sockaddr *) &cliaddr, len);
		}
		else{
			sendto(socketUdp->getSocketFd(), buffer, nread, MSG_CONFIRM,
               		(const sockaddr *) &cliaddr, len);
		}
	}
}

void Server::runCmd(bool& status)
{
	std::string cmd_buf {};
	while(status)
	{
		getline(std::cin, cmd_buf);
		if(cmd_buf == CMD_EXIT)
		{
			status = false;
			std::cout << "Closing app..." << std::endl;
		}
		else
		{
			printCmdHelp();
		}
	}
}

void Server::printCmdHelp()
{
	std::cout << "====HELP====" << std::endl;
	std::cout << "\t" << CMD_HELP << " - print cmd help" << std::endl;
	std::cout << "\t" << CMD_EXIT << " - stop and exit server app" << std::endl;
	std::cout << "============" << std::endl;
}