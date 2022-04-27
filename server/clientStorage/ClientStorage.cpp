#include "ClientStorage.hpp"

ClientStorage::~ClientStorage()
{
	std::stack<AcceptedClient*> removeStack {};
	for(auto client : storage)
	{
		removeStack.push(client.second);
	}
	while(!removeStack.empty())
	{
		auto tmp = removeStack.top();
		removeStack.pop();
		delete tmp;
	}
}

void ClientStorage::addClient(int client_fd)
{
	storage[client_fd] = new AcceptedClient(client_fd);
}

void ClientStorage::removeClient(int client_fd)
{
	if(storage.find(client_fd) != storage.end())
	{
		auto tmp = storage[client_fd];
		storage.erase(client_fd);
		delete tmp;
	}
}