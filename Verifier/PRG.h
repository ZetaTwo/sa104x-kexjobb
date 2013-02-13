#pragma once

#include <string>
#include <vector>

class PRG
{
public:
	PRG(std::vector<char> (*hash)(std::vector<char> data));
	~PRG(void);

	std::vector<char> operator()(std::vector<char> seed);
private:
	std::vector<char> (*hash)(std::vector<char> data);
};

