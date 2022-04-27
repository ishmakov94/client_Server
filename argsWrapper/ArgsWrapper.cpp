#include "ArgsWrapper.hpp"
#include <string.h>
#include <vector>

bool verifyIp(std::string& ipaddr)
{
    if (ipaddr.length())
    {
        std::vector<std::string> _ip;
        uint8_t pos = 0;
        uint8_t endPos = 0;
        while(endPos < ipaddr.length())
        {
            if(ipaddr[endPos] == '.')
            {
                _ip.push_back(ipaddr.substr(endPos - pos, pos));
                endPos++;
                pos = 0;
                
            }
            pos++;
            endPos++;
        }
        _ip.push_back(ipaddr.substr(endPos - pos, pos));
        if (_ip.size()==4)
        {
            for (int i=0; i < 4; i++)
            {
                for (int j=0; j < _ip[i].length(); j++)
                {
                    if (!isdigit(_ip[i][j])) 
                        return false;
                }
                if ((atoi(_ip[i].c_str()) < 0) || (atoi(_ip[i].c_str()) > 255))
                    return false;
            }
            return true;
        }
    }
    return false;
}

bool verifyPort(uint16_t port)
{
    return port > 1023 && port <= UINT16_MAX;
}

ArgsWrapper::ArgsWrapper(int argc, char const *argv[])
{
    bool isModeSet  = false;
    bool isProtoSet = false;
    bool isIpSet    = false;
    bool isPortSet  = false;

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-s") == 0)
        {
            if(!isModeSet)
            {
                mode.runMode = Mode::SERVER;
                isProtoSet   = true;
            }
            else
                std::cout << "The mode is already set with " << mode.toString() << std::endl;
        }
        if(strcmp(argv[i], "-c") == 0)
        {
            if(!isModeSet)
                mode.runMode = Mode::CLIENT;
            else
                std::cout << "The mode is already set with " << mode.toString() << std::endl;
        }
        if(strcmp(argv[i], "-t") == 0)
        {
            if(!isProtoSet)
                proto = Proto::TCP;
            else
                std::cout << "The protocol is already set with " 
                << (proto == Proto::TCP ? "TCP" : "UDP") << std::endl;
        }
        if(strcmp(argv[i], "-u") == 0)
        {
            if(!isProtoSet)
                proto = Proto::UDP;
            else
                std::cout << "The protocol is already set with " 
                << (proto == Proto::TCP ? "TCP" : "UDP") << std::endl;

        }
        if(strcmp(argv[i], "-i") == 0)
        {
            if(!isIpSet)
                if(i < argc - 1)
                    addr_ip = std::string(argv[i + 1]);
                else
                    std::cerr << "Incorrect ip addres" << std::endl;
            else
                std::cout << "The ip is already set with " << addr_ip << std::endl;
        }
        if(strcmp(argv[i], "-p") == 0)
        {
            if(!isPortSet)
                if(i < argc - 1)
                    port = atoi(argv[i + 1]);
                else
                    std::cerr << "Incorrect port" << std::endl;
            else
                std::cout << "The port is already set with " << port << std::endl;
        }
    }
}

bool ArgsWrapper::checkArgs()
{
    bool isOk = verifyIp(addr_ip);
    if(!isOk)
    {
        std::cerr << "Incorrect ip addres" << std::endl;
    }
    if(!(isOk &= verifyPort(port)))
    {
        std::cerr << "Incorrect port" << std::endl;
    }
    return isOk;
}

void ArgsWrapper::printHelp()
{
    std::cout << "Run: ./client_server [mode] [protocol] [ip] [port]" << std::endl;
    std::cout << "[mode]" << std::endl;
    std::cout << "\t-s - server (default)" << std::endl;
    std::cout << "\t-c - client" << std::endl;
    std::cout << "[protocol]" << std::endl;
    std::cout << "\t-u - udp (default)" << std::endl;
    std::cout << "\t-t - tcp" << std::endl;
    std::cout << "[ip]" << std::endl;
    std::cout << "\t-i (default 127.0.0.1)" << std::endl;
    std::cout << "Note: sould be formated X.X.X.X, where  0 <= X <= 255 (default 127.0.0.1)" << std::endl;
    std::cout << "[port]" << std::endl;
    std::cout << "\t-p (default 1024)" << std::endl;
    std::cout << "Note: sould be mode than 1024 and less than 65535 " << std::endl;
    std::cout << "Exapmles:" << std::endl;
    std::cout << "\t./client_server" << std::endl;
    std::cout << "\t./client_server -s -u -i 127.0.0.1 -p 1024" << std::endl;
    std::cout << "\t./client_server -c -t -i 127.0.0.1 -p 12346" << std::endl;
}

void ArgsWrapper::printStartMsg()
{
    std::cout << "Run with:" << std::endl;
    std::cout << "\t-mode " << mode.toString() << std::endl;
    std::cout << "\t-protocol " << (proto == Proto::TCP ? "TCP" : "UDP") << std::endl;
    std::cout << "\t-ip " << addr_ip << std::endl;
    std::cout << "\t-p " << port << std::endl;
}