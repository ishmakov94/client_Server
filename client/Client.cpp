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
	delete socket;
}

void Client::run()
{
	bool status = true;
	std::thread writterAndListenerThread([&status, this]()
	{
		while(status)
		{
			writter(status);
			status = listener(status);
		}
	});
	writterAndListenerThread.join();
}

void Client::writter(bool& status)
{
	int res = -1;
	if(status)
	{
		std::string w_buf {};
		std::cout << "Write msg: ";
		getline(std::cin, w_buf);
		if(w_buf == "#")
		{
			status = false;
		}
		else
		{
			if(socket->getProto() == Proto::TCP)
			{
				res = write(socket->getSocketFd(), w_buf.c_str(), w_buf.length());
			}
			else
			{
				res = sendto(socket->getSocketFd(), w_buf.c_str(), w_buf.length(), MSG_CONFIRM,
               		(const sockaddr *) &socket->getAddr(), sizeof(socket->getAddr()));
			}
		}
	}
	status = (res != -1);
}

bool Client::listener(bool& status)
{
	if(status)
	{
		socklen_t len = 0;
		memset(this->buffer, 0 ,BUFFER_SIZE);
		ssize_t nread;
		if(socket->getProto() == Proto::TCP)
		{
    		nread = read(socket->getSocketFd(), this->buffer, BUFFER_SIZE);
		}
		else
		{
			nread = recvfrom(socket->getSocketFd(), this->buffer, BUFFER_SIZE, MSG_WAITALL,
                 (sockaddr *) &socket->getAddr(), &len);
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
			std::cout << "Sever:" << this->buffer << std::endl;
		}
	}
	return status;
}