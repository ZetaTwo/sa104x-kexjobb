#pragma once

#include <queue>

#include "Node.h"

/** Pseudo random generator.
  * A class for creating pseudo random generators from a hash function.
  */
class PRG
{
public:
	/** Constructor.
	  * Constructs a PRG from a hash function, a seed and a the number of bits each element should be.
	  * \param[in] hash The hash function used in the PRG.
	  * \param[in] seed The seed used to initialize the PRG.
	  * \param[in] outbits The number of bits in each element of the PRG.
	  */
	PRG(bytevector (*hash)(bytevector data), bytevector seed, unsigned int outbits);
	~PRG(void);

	/** Return the next random number.
	  * Return the next random number from the PRG, generates new numbers if neccessary.
	  * \return The next random number from the PRG.
	  */
	IntLeaf next();
private:
	/** The hash function.
	  * The hash function used in the PRG.
	  */
	bytevector (*hash)(bytevector data);

	/** The current data.
	  * The current data which is hashed to a random element.
	  */
	bytevector data;

	/** Data queue
	  * The data which has been generated but not yet used as a random element.
	  */
	std::queue<unsigned char> dataqueue;
	
	/** Internal counter.
	  * The internal counter used to produce random elements.
	  */
	IntLeaf counter;

	/** Number of bits from the hash function.
	  * The number of bits in each element of the PRG.
	  */
	unsigned int outbits;
};

