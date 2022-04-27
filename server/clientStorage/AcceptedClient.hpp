#include <iostream>
#include <thread>
#include "../../common/Constants.hpp"
#include "../../common/Logic.hpp"
#include <unistd.h>
#include <cstring>

enum class Status : uint8_t
{
	CREATED,
	STOP,
	ALIVE
};

class AcceptedClient
{
public:
	AcceptedClient(int client_fd);
	~AcceptedClient();
	Status getStatus() {return status;};
	void run();

private:
	int client_fd;
	char* buffer;
	Status status;
	void listenAndWrite();

};