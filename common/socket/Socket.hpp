#pragma once

#include <iostream>
#include <string>
#include "../../argsWrapper/argsHelper/Proto.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

class Socket
{
public:
	Socket() = default;
	Socket(uint16_t port, Proto proto);
	~Socket();
	
	void listenAndAccept(int& fd);
	void inetPtonAndConnect(std::string& ip_addr);
	int getSocketFd() {return socket_fd;};
	Proto getProto() {return proto;}
	void _bind();
	int _listen(int backlog);
	int _accept();
	sockaddr_in& getAddr() {return addr;}
private:
	int socket_fd{-1};
	sockaddr_in addr{0};
	Proto proto;

	int createSocket(int domain, int type, int protocol);
	void _bind(int sockfd, const sockaddr *addr, socklen_t addrlen);
	void _connect(int sockfd, const sockaddr *addr, socklen_t addrlen);
	bool _inet_pton(int af, const char *src, void *dst);
};