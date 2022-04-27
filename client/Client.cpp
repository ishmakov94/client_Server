#include "Client.hpp"

Client::Client(std::string ip_addr, uint16_t port, Proto proto)
{
	socket = new Socket(port, proto);
	if(proto == Proto::TCP)
		socket->inetPtonAndConnect(ip_addr);
	buffer == new char[BUFFER_SIZE];
}

Client::~Client()
{
	delete buffer;
}

void Client::run()
{
	bool status = true;
	std::thread writterThread(&Client::writter, this, std::ref(status));
	std::thread listenerThread(&Client::listener, this, std::ref(status));
	writterThread.join();
	listenerThread.join();
}

void Client::writter(bool& status)
{
	while(status)
	{
		std::string w_buf {};
		getline(std::cin, w_buf);
		if(buffer[0] == '#')
		{
			status = false;
		}
		else
		{
			if(socket->getProto() == Proto::TCP)
			{
				write(socket->getSocketFd(), w_buf.c_str(), w_buf.length());
			}
			else
			{
				sendto(socket->getSocketFd(), w_buf.c_str(), w_buf.length(), MSG_CONFIRM,
               		(const sockaddr *) &socket->getAddr(), sizeof(socket->getAddr()));
			}
		}
	}
}

bool Client::listener(bool& status)
{
	while(status)
	{
		memset(buffer, 0 ,BUFFER_SIZE);
		ssize_t nread;
		if(socket->getProto() == Proto::TCP)
		{
    		nread = read(socket->getSocketFd(), buffer, BUFFER_SIZE);
		}
		else
		{
			nread = recvfrom(socket->getSocketFd(), buffer, BUFFER_SIZE, MSG_WAITALL,
                 (sockaddr *) &socket->getAddr(), (socklen_t *)sizeof(socket->getAddr()));
		}
		if (nread == -1) {
			perror("read failed");
			status = false;
		}
		if (nread == 0) {
			printf("EOF occured\n");
		}
		else
		{
			std::cout << "Sever:" << buffer << std::endl;
		}
	}
}