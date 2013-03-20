#include "ElGamal.h"

IntLeaf PDec(IntLeaf x, IntLeaf u, IntLeaf mod) {
	return u.expMod(-x, mod);
}

IntLeaf TDec(IntLeaf f, IntLeaf v, IntLeaf mod) {
	return v * f;
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