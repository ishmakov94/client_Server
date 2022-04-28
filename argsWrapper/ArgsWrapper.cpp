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

ArgsWrapper::ArgsWrapper(int argc, char const *argv[], bool isClient) : isClient(isClient)
{
    bool isProtoSet       = false;
    bool isIpSet          = false;
    bool isClientPortSet  = false;
    bool isTcpPortSet     = false;
    bool isUdpPortSet     = false;

    for(int i = 1; i < argc; i++)
    {
        if(isClient)
        {
            if(strcmp(argv[i], "-t") == 0)
            {
                if(!isProtoSet)
                {
                    proto = Proto::TCP;
                    isProtoSet = true;
                }
                else
                    std::cout << "The protocol is already set with " 
                    << (proto == Proto::TCP ? "TCP" : "UDP") << std::endl;
            }
            if(strcmp(argv[i], "-u") == 0)
            {
                if(!isProtoSet)
                {
                    proto = Proto::UDP;
                    isProtoSet = true;
                }
                else
                    std::cout << "The protocol is already set with " 
                    << (proto == Proto::TCP ? "TCP" : "UDP") << std::endl;
            }
            if(strcmp(argv[i], "-i") == 0)
            {
                if(!isIpSet)
                    if(i < argc - 1)
                    {
                        addr_ip = std::string(argv[i + 1]);
                        isIpSet = true;
                    }
                    else
                        std::cerr << "Incorrect ip addres" << std::endl;
                else
                    std::cout << "The ip is already set with " << addr_ip << std::endl;
            }
            if(strcmp(argv[i], "-p") == 0)
            {
                if(!isClientPortSet)
                    if(i < argc - 1)
                    {
                        clientPort = atoi(argv[i + 1]);
                        isClientPortSet = true;
                    }
                    else
                        std::cerr << "Incorrect port" << std::endl;
                else
                    std::cout << "The port is already set with " << clientPort << std::endl;
            }
        }
        else
        {
            if(strcmp(argv[i], "-tcp-port") == 0)
            {
                if(!isTcpPortSet)
                    portTcp = atoi(argv[i + 1]);
                else
                    std::cout << "The tcpPort is already set with " << portTcp << std::endl;
            }
            if(strcmp(argv[i], "-udp-port") == 0)
            {
                if(!isUdpPortSet)
                    portUdp = atoi(argv[i + 1]);
                else
                    std::cout << "The portUdp is already set with " << portUdp << std::endl;
            }
        }
    }
}

bool ArgsWrapper::checkArgs()
{
    bool isOk = true;
    if(isClient) 
    {
        isOk = verifyIp(addr_ip);
        if(!isOk)
        {
            std::cerr << "Incorrect ip addres" << std::endl;
        }
        if(!(isOk &= verifyPort(clientPort)))
        {
            std::cerr << "Incorrect client port" << std::endl;
        }
    }
    else
    {
        if(portTcp == portUdp)
        {
            std::cerr << "Tcp port is equal Udp port" << std::endl;
            return false;
        } 
        if(!(isOk &= verifyPort(portTcp)))
        {
            std::cerr << "Incorrect Tcp port" << std::endl;
        }
        if(!(isOk &= verifyPort(portUdp)))
        {
            std::cerr << "Incorrect Udp port" << std::endl;
        }
    }
    return isOk;
}

void ArgsWrapper::printHelp()
{
    if(isClient)
    {
        std::cout << "Run: ./client [protocol] [ip] [port]" << std::endl;
        std::cout << "[protocol]" << std::endl;
        std::cout << "\t-u - udp (default)" << std::endl;
        std::cout << "\t-t - tcp" << std::endl;
        std::cout << "[ip]" << std::endl;
        std::cout << "\t-i (default 127.0.0.1)" << std::endl;
        std::cout << "Note: sould be formated X.X.X.X, where  0 <= X <= 255 (default 127.0.0.1)" << std::endl;
        std::cout << "[port]" << std::endl;
        std::cout << "\t-p (default 1024)" << std::endl;
        std::cout << "Note: sould be mode than 1024 and less than 65535" << std::endl;
        std::cout << "Exapmles:" << std::endl;
        std::cout << "\t./client" << std::endl;
        std::cout << "\t./client -u -i 127.0.0.1 -p 1024" << std::endl;
        std::cout << "\t./client -t -i 127.0.0.1 -p 12346" << std::endl;
    }
    else
    {
        std::cout << "Run: ./server [portTcp] [portUdp]" << std::endl;
        std::cout << "[portTcp]" << std::endl;
        std::cout << "\t-tcp-port (default 1024)" << std::endl;
        std::cout << "Note: sould be more than 1024 and less than 65535 and is not equal Udp port" << std::endl;
        std::cout << "\t-udp-port (default 1025)" << std::endl;
        std::cout << "Note: sould be more than 1024 and less than 65535 and is not equal Tcp port" << std::endl;
        std::cout << "Exapmles:" << std::endl;
        std::cout << "\t./server" << std::endl;
        std::cout << "\t./server -tcp-port 1024 -udp-port 1204" << std::endl;
    }
    
}

void ArgsWrapper::printStartMsg()
{
    if(isClient)
    {
        std::cout << "Client run with:" << std::endl;
        std::cout << "\t-protocol " << (proto == Proto::TCP ? "TCP" : "UDP") << std::endl;
        std::cout << "\t-ip " << addr_ip << std::endl;
        std::cout << "\t-p " << clientPort << std::endl;
    }
    else
    {
        std::cout << "Server run with:" << std::endl;
        std::cout << "\t-tcp-port " << portTcp << std::endl;
        std::cout << "\t-udp-port " << portUdp << std::endl;
    }
}