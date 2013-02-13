#include "PRG.h"


PRG::PRG(std::vector<char> (*hash)(std::vector<char> data)) : hash(hash)
{
}

PRG::~PRG(void)
{
}

std::vector<char> PRG::operator()(std::vector<char> seed) {
	return hash(seed);
}