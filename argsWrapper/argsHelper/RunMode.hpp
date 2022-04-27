#pragma once

#include <iostream>
#include <string>

enum class Mode : uint8_t
{
	SERVER,
	CLIENT
};

class RunMode final
{
public:
	RunMode()                    = delete;
	RunMode(const RunMode& mode) = delete;
	RunMode(RunMode&& mode)      = delete;
	~RunMode()                   = default;

	RunMode(Mode mode) : runMode(mode){};

	Mode runMode;

	std::string toString()
	{
		switch (runMode)
		{
			case Mode::SERVER: return "SERVER";
			case Mode::CLIENT: return "CLIENT";
			default:
			{
				std::cerr << "Undefined mode" << std::endl;
				return "Undefined";
			}
		}
	}

};
