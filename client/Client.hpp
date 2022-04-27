#include "../common/socket/Socket.hpp"
#include "../common/Constants.hpp"
#include <iostream>
#include <cstring>
#include <thread>

class Client
{
public:
	Client() = default;
	~Client();
	Client(std::string ip_addr, uint16_t port, Proto proto);
	void run();
private:
	Socket* socket;
	char* buffer;
	void writter(bool& status);
	bool listener(bool& status);
};