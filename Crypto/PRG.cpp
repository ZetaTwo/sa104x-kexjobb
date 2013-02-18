#include "PRG.h"

PRG::PRG(std::vector<unsigned char> (*hash)(std::vector<unsigned char> data), std::vector<unsigned char> seed) : hash(hash), counter(0), data(seed)
{
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);
}

PRG::~PRG(void)
{
}

IntLeaf PRG::next() {
	std::vector<unsigned char> count = counter.toVector();
	counter += 1;

	std::copy(data.end()-4, data.end(), count.begin());

	return static_cast<IntLeaf>(hash(data));
}