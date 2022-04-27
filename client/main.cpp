
#include <iostream>
#include "../argsWrapper/ArgsWrapper.hpp"
#include "Client.hpp"

int main(int argc, char const *argv[])
{
	ArgsWrapper argsWrapper(argc, argv, true);
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
		Client client(argsWrapper.getIpAddr(), argsWrapper.getClientPort(), argsWrapper.getProtocol());
		client.run();
	}
	std::cout << "Close app" << std::endl;
	return 0;
}
