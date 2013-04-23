#include "RandomArray.h"

Node RandomArray(Node Gq, unsigned int Nprime, bytevector (*hash)(bytevector data), bytevector seed, unsigned int Nr) {

	IntLeaf p = Gq.getIntLeafChild(0);
	IntLeaf q = Gq.getIntLeafChild(1);

    unsigned int Nq = p.getBitLength();
	PRG prg(hash, seed, 8*((Nq+Nr+8-1)/8));
	IntLeaf mod(2);
	mod.expTo(Nq+Nr);


	Node result;
	for (int i = 0; i < Nprime; i++)
	{
		IntLeaf child = prg.next();
		child.modTo(mod);
        IntLeaf exp = (p - 1) / q;
        std::string expdata = exp.toString();
		child.expToMod(exp, p);
		result.addChild(child);
	}

	return result;
}