#pragma once

#include <iostream>

inline std::pair<bool, int> findSum(char* buffer, ssize_t& bufSize)
{
	std::string w_buff{};
	bool isSum = false;
	int sum = 0;
	int i = 0;
	while(i < bufSize)
	{
		if(isdigit(buffer[i]))
		{
			w_buff.push_back(buffer[i]);
			if(i < bufSize - 1)
			{
				if(!isdigit(buffer[i + 1]))
				{
					sum += atoi(w_buff.c_str());
					w_buff = "";
				}
			}
			else
			{
				sum += atoi(w_buff.c_str());
				w_buff = "";
			}
			isSum = true;
		}
		i++;
	}
	return {isSum, sum};
}
