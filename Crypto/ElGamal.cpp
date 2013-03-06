#include "ElGamal.h"

IntLeaf PDec(IntLeaf x, Node c, IntLeaf mod) {
	return c.getIntLeafChild(0).expMod(-x, mod);
}

IntLeaf TDec(Node x, Node c, IntLeaf mod) {
	return c.getIntLeafChild(1) * c.getIntLeafChild(0).expMod(-x.sum(), mod);
}

Node Enc(Node pk, IntLeaf m, IntLeaf s, IntLeaf mod) {
	Node result;

	//IntLeaf s(); <-- Choose at random

	IntLeaf y = pk.getIntLeafChild(0);
	IntLeaf g = pk.getIntLeafChild(1);

	result.addChild(g.expMod(s, mod));
	result.addChild(g.expMod(y, mod).expMod(s, mod).multMod(m, mod));
	return result;
}