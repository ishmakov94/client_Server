#include "AcceptedClient.hpp"

AcceptedClient::AcceptedClient(int client_fd) : client_fd(client_fd)
{
	buffer = new char[BUFFER_SIZE];
	status = Status::CREATED;
}
AcceptedClient::~AcceptedClient()
{
	delete buffer;
}
void AcceptedClient::run()
{
	std::thread listenAndWriteThread(&AcceptedClient::listenAndWrite, this);
	listenAndWriteThread.detach();
}
void AcceptedClient::listenAndWrite()
{
	while(status == Status::CREATED || status == Status::ALIVE)
	{
		memset(buffer, 0, BUFFER_SIZE);
		ssize_t nread = read(client_fd, buffer, BUFFER_SIZE);
		if (nread == -1) {
			perror("read failed");
			status = Status::STOP;
		}
		if (nread == 0) {
			printf("EOF occured\n");
		}
		else
		{
			auto sum = findSum(buffer, nread);
			if(sum.first)
			{
				std::string w_buf = std::to_string(sum.second);
				write(client_fd, w_buf.c_str(), w_buf.length());
			}
			else
			{
				write(client_fd, buffer, nread);
			}
			status = Status::ALIVE;
		}
	}
}
