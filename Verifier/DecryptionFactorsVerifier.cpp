#include "DecryptionFactorsVerifier.h"

bool DecryptionFactorsVerifier(j, Rho, N, nE, nR, nV, PRG, Gq, Node y, Cw, Mw, w, f, tauDec, sigmaDec) {

	//Step 1
	//Foreach tauDecL in tauDec {
		//if(tauDecL.getChild(0) is not in Gq || tauDecL.getChild(1) is not in Mw) {
			//return false;
		//}
	//}

	//Foreach sigmaDecL in sigmaDec {
		//if(sigmaDecl is not in Zq) {
			//return false;
		//}
	//

	//Step 2
	s = RO_seed(rho, Node(Node(g, w), Node(a, b)));
	a = Node(y);
	b = Node(f);

	//Step 3
	//array t = PRG(s)
	//e_i = t_i mod 2^nE

	//Step 4
	v = RO_challenge(rho, Node(Leaf(s), Node(tauDec)))

	//Step 5
	A = u.expMult(e);
	if(j == 0) {
		B = f.prod().expMult(e);
		//Some more calculations
		//If fail: return false;
	} else {
		//Some other calculations
		//If fail: return false;
	}

	return true;
}