#include "RO.h"


RO::RO(bytevector (*hash)(bytevector data), int Nout) : hash(hash), Nout(Nout)
{
}

RO::~RO(void)
{
}

IntLeaf RO::operator()(bytevector data) {
	bytevector seed = Nout.toVector();
	seed.insert(seed.end(), data.begin(), data.end());

	return static_cast<IntLeaf>(hash(seed));
}