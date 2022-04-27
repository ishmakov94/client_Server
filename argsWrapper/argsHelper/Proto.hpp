#pragma once

#include <iostream>
#include <string>

enum class Proto : uint8_t
{
	TCP,
	UDP
};

class Protocol final
{
public:
	Protocol()                 = default;
	~Protocol()                = default;

	Protocol(Proto proto) : proto(proto){};

	Proto proto;
	
	std::string toString()
	{
		switch (proto)
		{
			case Proto::TCP: return  "TCP";
			case Proto::UDP: return  "UDP";
			default:
			{
				std::cerr << "Undefined protocol" << std::endl;
				return "Undefined";
			}
		}
	}

};