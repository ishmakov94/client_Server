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

    ArgsWrapper(int argc, char const *argv[]);
    
    bool checkArgs();
    
    void printHelp();

    void printStartMsg();

    bool isServerMode() {return mode.runMode == Mode::SERVER;}

    uint16_t getPort() {return port;}

    Proto getProtocol() {return proto;};

    std::string getIpAddr() {return addr_ip;};

private:
    RunMode     mode    {Mode::SERVER};
    Proto       proto   {Proto::UDP};
    std::string addr_ip {"127.0.0.1"};
    uint16_t    port    {1024};
};