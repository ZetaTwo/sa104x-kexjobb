#include "RandomArray.h"

Node RandomArray(Node Gq, unsigned int Nprime, std::vector<unsigned char> (*hash)(std::vector<unsigned char> data), std::vector<unsigned char> seed, unsigned int Nr) {

	IntLeaf p = static_cast<IntLeaf &>(Gq.getChild(0));
	IntLeaf q = static_cast<IntLeaf &>(Gq.getChild(1));;

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