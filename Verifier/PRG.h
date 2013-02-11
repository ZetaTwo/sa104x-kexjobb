#pragma once

#include <string>

class PRG
{
public:
	PRG();
	~PRG(void);

	virtual void Generate(std::string seed) = 0;
};

