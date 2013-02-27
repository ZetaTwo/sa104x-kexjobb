#include "PRG.h"

PRG::PRG(std::vector<unsigned char> (*hash)(std::vector<unsigned char> data), std::vector<unsigned char> seed, unsigned int outbits) : hash(hash), counter(0, sizeof(uint32_t)), data(seed), outbits(outbits) 
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
	while(dataqueue.size() < outbits/8) {
		std::vector<unsigned char> count = counter.toVector();
		counter += 1;

		std::copy(count.begin(), count.end(), data.end()-4);

		std::vector<unsigned char> hashed = hash(data);
		for(std::vector<unsigned char>::iterator itr = hashed.begin(); itr != hashed.end(); itr++) {
			dataqueue.push(*itr);
		}
	}

	std::vector<unsigned char> result;
	for (int i = 0; i < outbits/8; i++)
	{
		result.push_back(dataqueue.front());
		dataqueue.pop();
	}

	return static_cast<IntLeaf>(result);
}