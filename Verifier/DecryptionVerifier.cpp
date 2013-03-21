#include "DecryptionVerifier.h"
#include "DecryptionFactorsVerifier.h"

#include "ProofOfShuffle.h"
#include "ElGamal.h"

#include "Node.h"

bool DecryptionVerifier(const proofStruct &ps, const Node L, const Node m) {

	IntLeaf p = ps.Gq.getIntLeafChild(0);

	//Step 1
	Node f = Node("f.dat");
	Node tauDec = Node("tauDec.dat");
	Node sigmaDec = Node("sigmaDec.dat");

	//If fail, return false;

	//Step 2
	bool result = DecryptionFactorsVerifier(0, ps, f, tauDec, sigmaDec, L);

	if(!result) {
		//Step 3
		for (int l = 0; l < f.getLength(); l++)
		{
			result = DecryptionFactorsVerifier(l, ps, f, tauDec, sigmaDec, L);

			IntLeaf xL = ps.x.getIntLeafChild(l);
			

			if(!result && (xL == BOTTOM || f.getIntLeafChild(l) != PDec(xL, L.getIntLeafChild(l), p))) {
				return false;
			}
		}
	}

	//Step 4
	IntLeaf x = f.prod();
	for(int i = 0; i < L.getLength(); i++) {
		if(m.getIntLeafChild(i) != TDec(L.getIntLeafChild(i), x, p)) {
			return false;
		}
	}

	return true;
}
