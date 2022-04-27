#include "ClientStorage.hpp"
#include <stack>
#include <mutex>
#include <unistd.h>

class ClientStorageManager
{
public:
	ClientStorageManager()
	{
		storage = new ClientStorage();
	};
	~ClientStorageManager()
	{
		delete storage;
	};

	void addClient(int client_fd) { storage->addClient(client_fd);};
	void run(bool& status);
private:
	ClientStorage* storage;
	std::mutex storageMutex;
};