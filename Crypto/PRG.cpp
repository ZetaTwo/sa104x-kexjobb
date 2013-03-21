#include "PRG.h"

PRG::PRG(bytevector (*hash)(bytevector data), bytevector seed, unsigned int outbits) : hash(hash), counter(0, sizeof(uint32_t)), data(seed), outbits(outbits) 
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
		bytevector count = counter.toVector();
		counter += 1;

		std::copy(count.begin(), count.end(), data.end()-4);

		bytevector hashed = hash(data);
		for(bytevector::iterator itr = hashed.begin(); itr != hashed.end(); itr++) {
			dataqueue.push(*itr);
		}
	}

	bytevector result;
	for (int i = 0; i < outbits/8; i++)
	{
		result.push_back(dataqueue.front());
		dataqueue.pop();
	}

	return static_cast<IntLeaf>(result);
}