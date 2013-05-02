#include "PRG.h"

PRG::PRG(bytevector (*hash)(bytevector data), bytevector seed, unsigned int outbits) : hash(hash), counter(0, sizeof(uint32_t)), data(seed), outbits(outbits) 
{
	//Initialize the counter part of the data to 4 bytes of zero.
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);
}

PRG::~PRG(void)
{
}

IntLeaf PRG::next() {
	//While we don't have enough data
	while(dataqueue.size() < outbits/8) {
		//Get the counter data and then increase the counter.
		bytevector count = counter.toVector();
		counter += 1;

		//Copy the counter data to the last 4 bytes of the data
		std::copy(count.begin(), count.end(), data.end()-4);

		//Hash the data and append it to the data queue.
		bytevector hashed = hash(data);
		for(bytevector::iterator itr = hashed.begin(); itr != hashed.end(); itr++) {
			dataqueue.push(*itr);
		}
	}

	//Prepare the result and fill it with enough data from the queue.
	bytevector result;
	for (unsigned int i = 0; i < outbits/8; i++)
	{
		result.push_back(dataqueue.front());
		dataqueue.pop();
	}

	//Create an IntLeaf from the data and return the result.
	return static_cast<IntLeaf>(result);
}