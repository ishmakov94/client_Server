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
	std::thread udpThread(&Server::runUdp, this);
	storageManagerThread.join();
	tcpTread.join();
	udpThread.join();
}

void Server::runTcp(bool& status, ClientStorageManager* clientStorageManager)
{
	while(status)
	{
		int fd = -1;
		socketTcp->listenAndAccept(fd);
		if(fd != -1)
		{
			clientStorageManager->addClient(fd);
		}
	}
}
void Server::runUdp()
{
	bool status = true;
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