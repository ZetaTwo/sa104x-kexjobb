#include "Algorithm26.h"
#include "Algorithm22.h"

#include "Node.h"

bool algorithm26(rho, N, nE, nR, nV, PRG, Gq, Mw, Cw, pk, Node y, L, m) {

	//Step 1
	Node f = Node("f.dat");
	Node tauDec = Node("tauDec.dat");
	Node sigmaDec = Node("sigmaDec.dat");
	//If fail, return false;

	//Step 2
	bool result = algorithm22(0, rho, N, nE, nR, nV, PRG, Gq, g, y, Cw, Mw, L, f, tauDec, sigmaDec);

	if(!result) {
		//Step 3
		for (int l = 0; l < lambda; l++)
		{
			result = algorithm22(l, rho, N, nE, nR, nV, PRG, Gq, g, y, Cw, Mw, L, f, tauDec, sigmaDec);
			if(!result && (xL = BOTTOM || fL != PDec(xL, L))) {
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