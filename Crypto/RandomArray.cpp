#include "RandomArray.h"

Node RandomArray(Node Gq, unsigned int Nprime, bytevector (*hash)(bytevector data), bytevector seed, unsigned int Nr) {

	IntLeaf p = Gq.getIntLeafChild(0);
	IntLeaf q = Gq.getIntLeafChild(1);

    unsigned int Nq = p.getBitLength();
	PRG prg(hash, seed, 8*((Nq+Nr+8-1)/8));
	IntLeaf mod(2);
	mod.expTo(Nq+Nr);

	Node result;
	for (unsigned int i = 0; i < Nprime; i++)
	{
		IntLeaf child = prg.next(); //t = PRG()
		child.modTo(mod); //t' = t mod 2^(Nq+Nr)

        IntLeaf exp = (p - 1) / q; // ^((p-1)/q)
		child.expToMod(exp, p); //h = t' ^((p-1)/q) mod p

		result.addChild(child);
	}

	return result;
}