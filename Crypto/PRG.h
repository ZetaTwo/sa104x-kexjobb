#pragma once

#include "Node.h"

#include <string>
#include <vector>
#include <queue>

class PRG
{
public:
	PRG(bytevector (*hash)(bytevector data), bytevector seed, unsigned int outbits);
	~PRG(void);

	IntLeaf next();
private:
	bytevector (*hash)(bytevector data);
	bytevector data;
	std::queue<unsigned char> dataqueue;
	IntLeaf counter;
	unsigned int outbits;
};

