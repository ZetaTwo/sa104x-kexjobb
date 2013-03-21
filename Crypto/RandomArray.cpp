#include "RandomArray.h"

Node RandomArray(Node Gq, unsigned int Nprime, bytevector (*hash)(bytevector data), bytevector seed, unsigned int Nr) {

	IntLeaf p = Gq.getIntLeafChild(0);
	IntLeaf q = Gq.getIntLeafChild(1);

	unsigned int Nq = p.getLength() * 8;
	PRG prg(hash, seed, Nq+Nr);
	IntLeaf mod(2);
	mod.expTo(Nq+Nr);


	Node result;
	for (int i = 0; i < Nprime; i++)
	{
		IntLeaf child = prg.next();
		child.modTo(mod);
		child.expToMod((p + (-1)).mult(q.inverse(p)), p);
		result.addChild(child);
	}

	return result;
}