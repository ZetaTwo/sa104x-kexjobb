#include "RO.h"


RO::RO(std::vector<unsigned char> (*hash)(std::vector<unsigned char> data), int Nout) : hash(hash), Nout(Nout)
{
}

RO::~RO(void)
{
}

IntLeaf RO::operator()(std::vector<unsigned char> data) {
	std::vector<unsigned char> seed = Nout.toVector();
	seed.insert(seed.end(), data.begin(), data.end());

	return static_cast<IntLeaf>(hash(seed));
}