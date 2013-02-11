#pragma once

#include "PRG.h"

class SHA256_PRG :
	public PRG
{
public:
	SHA256_PRG(void);
	~SHA256_PRG(void);

	virtual void Generate(std::string seed);
};

