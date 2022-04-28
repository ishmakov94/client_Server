#include "Socket.hpp"

Socket::Socket(uint16_t port, Proto proto)
{
	addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    this->proto = proto;
    switch (proto)
    {
        case Proto::TCP:
            socket_fd = createSocket(addr.sin_family, SOCK_STREAM, 0);
            break;
        case Proto::UDP:
            socket_fd = createSocket(addr.sin_family, SOCK_DGRAM, 0);
            break;
    }
//     int flags = fcntl(socket_fd, F_GETFL, 0);
//     flags |= O_NONBLOCK;
//     fcntl(socket_fd, F_SETFL, flags);
}

Socket::~Socket()
{
    printf("%s\n", __func__);
	addr = {0};
	close(socket_fd);
}

int Socket::createSocket(int domain, int type, int protocol) {
    int fd = socket(domain, type, protocol);
    if (fd == -1) {
        perror("Socket creating is failed");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void Socket::_bind()
{
	std::cout << __func__ << ": socket_fd " << socket_fd << std::endl;
	_bind(socket_fd, (sockaddr *) &addr, sizeof(addr));
}

void Socket::_bind(int sockfd, const sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Bind is failed");
        exit(EXIT_FAILURE);
    }
}

void Socket::listenAndAccept(int& fd)
{
	if(this->_listen(5) != -1)
	{
		fd = this->_accept();
	}
}

void Socket::inetPtonAndConnect(std::string& ip_addr)
{
	bool isOk = _inet_pton(addr.sin_family, ip_addr.c_str(), &addr.sin_addr);
	if(isOk)
	{
		_connect(socket_fd, (sockaddr *) &addr, sizeof(addr));
	}
}

int Socket::_listen(int backlog) {
    int res = listen(socket_fd, backlog);
    if (res == -1) {
        perror("Listen failed");
    }
	return res;
}

int Socket::_accept() {
	socklen_t adr_size = sizeof(addr);
    int res = accept(socket_fd, (sockaddr *) &addr, &adr_size);
    if (res == -1) {
        perror("accept failed");
    }
    return res;
}

void Socket::_connect(int sockfd, const sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

bool Socket::_inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
    }
    if (res == -1) {
        perror("inet_pton failed");
    }
	return res != -1 && res != 0;
}