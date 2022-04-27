#pragma once

#include <iostream>
#include "argsHelper/RunMode.hpp"
#include "argsHelper/Proto.hpp"

class ArgsWrapper
{
public:
    ArgsWrapper()                = delete;
    ArgsWrapper(ArgsWrapper& X)  = delete;
    ArgsWrapper(ArgsWrapper&& X) = delete;
    ~ArgsWrapper()               = default;

    ArgsWrapper(int argc, char const *argv[], bool isClient);
    
    bool checkArgs();
    
    void printHelp();

    void printStartMsg();

    uint16_t getTcpPort() {return portTcp;}

    uint16_t getUdpPort() {return portUdp;}

    uint16_t getClientPort() { return clientPort;};

    Proto getProtocol() {return proto;};

    std::string getIpAddr() {return addr_ip;};

private:
    bool        isClient   {false};
    Proto       proto      {Proto::UDP};
    std::string addr_ip    {"127.0.0.1"};
    uint16_t    portTcp    {1024};
    uint16_t    portUdp    {1025};
    uint16_t    clientPort {1024};
};