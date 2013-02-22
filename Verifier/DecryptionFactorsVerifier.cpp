#include "DecryptionFactorsVerifier.h"

#include "Node.h"
#include "RO.h"
#include "PRG.h"
#include "H_SHA.h"

bool DecryptionFactorsVerifier(const int j, const proofStruct &ps, const Node &f, const Node &tauDec, const Node &sigmaDec) {

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
	//Construct seed
	Node seed;
	Node seed_a;
	Node seed_b;
	seed_a.addChild(static_cast<const Node *>(ps.Gq)->getChild(2));
	seed_a.addChild(*ps.w);
	seed_b.addChild(*ps.pk);
	seed_b.addChild(f);
	seed.addChild(seed_a);
	seed.addChild(seed_b);

	std::vector<unsigned char> seed_data;
	std::vector<unsigned char> rho_data = ps.rho->toVector();
	std::vector<unsigned char> seed_data_a = seed.toVector();
	seed_data.insert(seed_data.begin(), rho_data.begin(), rho_data.end());
	seed_data.insert(seed_data.begin(), seed_data_a.begin(), seed_data_a.end());

	RO RO_seed(H_SHA256, 1);
	IntLeaf s = RO_seed(seed_data);

	//Step 3
	PRG prg(H_SHA256, s.toVector());
	Node t;
	for (int i = 0; i < ps.N; i++)
	{
		t.addChild(prg.next());
	}
	IntLeaf mod(2);
	mod.expTo(ps.nE);
	Node e = t.mod(mod);

	//Step 4
	Node challenge;
	challenge.addChild(s);
	challenge.addChild(tauDec);
	std::vector<unsigned char> challenge_data;
	std::vector<unsigned char> challenge_data_a = challenge.toVector();
	challenge_data.insert(challenge_data.begin(), rho_data.begin(), rho_data.end());
	challenge_data.insert(challenge_data.begin(), challenge_data_a.begin(), challenge_data_a.end());

	RO RO_challenge(H_SHA256, 1);
	IntLeaf v = RO_challenge(challenge_data);

	//Step 5
	Node u;
	for (int i = 0; i < ps.w->getLength(); i++)
	{
		u.addChild(static_cast<const Node &>(ps.w->getChild(i)).getChild(0));
	}
	IntLeaf A = u.expMultMod(e, static_cast<const IntLeaf &>(ps.Gq->getChild(0)));
	if(j == 0) {

		Node B = f.prod().expMult(e);
		//Some more calculations
		//If fail: return false;
	} else {
		//Some other calculations
		//If fail: return false;
	}

	return true;
}