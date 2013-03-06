#include "DecryptionVerifier.h"
#include "DecryptionFactorsVerifier.h"

#include "ProofOfShuffle.h"
#include "ElGamal.h"

#include "Node.h"

bool DecryptionVerifier(const proofStruct &ps, const Node L, const Node m) {

	//Step 1
	Node f = Node("f.dat");
	Node tauDec = Node("tauDec.dat");
	Node sigmaDec = Node("sigmaDec.dat");
	//If fail, return false;

	//Step 2
	bool result = DecryptionFactorsVerifier(0, ps, f, tauDec, sigmaDec);

	if(!result) {
		//Step 3
		for (int l = 0; l < f.getLength(); l++)
		{
			result = DecryptionFactorsVerifier(l, ps, f, tauDec, sigmaDec);
			if(!result && (xL = BOTTOM || f.getIntLeafChild(l) != PDec(xL, L))) {
				return false;
			}
		}
	}

	//Step 4
	if(m != TDec(L, f.prod())) {
		return false;
	}

	return true;
}