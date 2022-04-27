#include <iostream>
#include "argsWrapper/ArgsWrapper.hpp"
#include "server/Server.hpp"
#include "client/Client.hpp"

int main(int argc, char const *argv[])
{
	ArgsWrapper argsWrapper(argc, argv);
	bool isStartOk = argsWrapper.checkArgs();
	if(isStartOk)
	{
		argsWrapper.printStartMsg();
	}
	else
	{
		argsWrapper.printHelp();
		exit(0);
	}

	if(isStartOk)
	{
		if(argsWrapper.isServerMode())
		{
			Server server(argsWrapper.getPort());
			server.run();
		}
		else
		{
			Client client(argsWrapper.getIpAddr(), argsWrapper.getPort(), argsWrapper.getProtocol());
			client.run();
		}
	}
	std::cout << "Close app" << std::endl;
	return 0;
}

//TODO:
// UDP client
