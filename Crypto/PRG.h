#pragma once

#include "Node.h"

#include <string>
#include <vector>
#include <queue>

class PRG
{
public:
	PRG(std::vector<unsigned char> (*hash)(std::vector<unsigned char> data), std::vector<unsigned char> seed, unsigned int outbits);
	~PRG(void);

	IntLeaf next();
private:
	std::vector<unsigned char> (*hash)(std::vector<unsigned char> data);
	std::vector<unsigned char> data;
	std::queue<unsigned char> dataqueue;
	IntLeaf counter;
	unsigned int outbits;
};

