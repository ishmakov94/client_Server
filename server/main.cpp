
#include <iostream>
#include "../argsWrapper/ArgsWrapper.hpp"
#include "Server.hpp"

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
		// Server server(argsWrapper.getPort());
		// server.run();
	}
	std::cout << "Close app" << std::endl;
	return 0;
}
