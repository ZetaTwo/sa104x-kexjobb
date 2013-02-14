#include "ElGamal.h"

IntLeaf PDec(IntLeaf x, Node c, IntLeaf mod) {
	return static_cast<IntLeaf &>(c.getChild(0)).expMod(-x, mod);
}

IntLeaf TDec(Node x, Node c, IntLeaf mod) {
	return static_cast<IntLeaf &>(c.getChild(1)) *
		static_cast<IntLeaf &>(c.getChild(0)).expMod(-x.sum(), mod);
}

Node Enc(IntLeaf pk, IntLeaf m, IntLeaf s, IntLeaf g, IntLeaf mod) {
	Node result;
	//IntLeaf s(); <-- Choose at random

	result.addChild(g.expMod(s, mod));
	result.addChild(g.expMod(pk, mod).expMod(s, mod).multMod(m, mod));
	return result;
}