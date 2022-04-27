#include "AcceptedClient.hpp"
#include <unordered_map>
#include <stack>

using StorageMap = std::unordered_map<int, AcceptedClient*>;

class ClientStorage
{
public:
	ClientStorage() = default;
	~ClientStorage();
	void addClient(int client_fd);
	void removeClient(int client_fd);
	bool isEmpty() { return storage.empty();};
	StorageMap getStorage() {return storage;};
private:
	StorageMap storage;
};