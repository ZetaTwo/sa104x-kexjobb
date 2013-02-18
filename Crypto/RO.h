#pragma once

#include "Node.h"

#include <string>
#include <vector>

class RO
{
public:
	RO(std::vector<unsigned char> (*hash)(std::vector<unsigned char> data), int Nout);
	~RO(void);

	IntLeaf operator()(std::vector<unsigned char> data);
private:
	std::vector<unsigned char> (*hash)(std::vector<unsigned char> data);
	IntLeaf Nout;
};

