#pragma once

#include "Node.h"

#include <string>
#include <vector>

class PRG
{
public:
	PRG(std::vector<char> (*hash)(std::vector<unsigned char> data), std::vector<unsigned char> seed);
	~PRG(void);

	IntLeaf next();
private:
	std::vector<char> (*hash)(std::vector<unsigned char> data);
	std::vector<unsigned char> data;
	IntLeaf counter;
};

