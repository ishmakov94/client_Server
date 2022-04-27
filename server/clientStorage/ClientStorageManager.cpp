#include "ClientStorageManager.hpp"

void ClientStorageManager::run(bool& status)
{
	std::stack<int> removeStack {};	
	while(status)
	{
		sleep(2);
		if(storage->isEmpty()) continue;
		storageMutex.lock();
		for(auto client : storage->getStorage())
		{
			if(client.second->getStatus() == Status::CREATED)
			{
				client.second->run();
			}
			if(client.second->getStatus() == Status::STOP)
			{
				removeStack.push(client.first);
			}
		}
		while(!removeStack.empty())
		{
			storage->removeClient(removeStack.top());
			removeStack.pop();
		}
		storageMutex.unlock();
	}
}