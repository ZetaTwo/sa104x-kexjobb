#include <cmath>

#include "RO.h"
#include "PRG.h"


RO::RO(bytevector (*hash)(bytevector data), int Nout) : hash(hash), Nout(Nout)
{
}

RO::~RO(void)
{
}

IntLeaf RO::operator()(bytevector data) {
	IntLeaf NoutLeaf(Nout, 4);
	bytevector seed = NoutLeaf.toVector();
	seed.insert(seed.end(), data.begin(), data.end());
	seed = hash(seed);

	PRG prg(hash, seed, Nout);
	bytevector result;
	unsigned int targetN = ceil(Nout/8.0);
	while(result.size() < targetN) {
		IntLeaf next = prg.next();
		bytevector nextData = next.toVector();
		result.insert(result.end(), nextData.begin(), nextData.end());
	}

	result[0] &= ((char)pow(2, (Nout % 8))-1);
	result.resize(targetN);

	return IntLeaf(result);
}