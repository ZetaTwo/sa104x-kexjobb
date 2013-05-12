#include "DecryptionFactorsVerifier.h"

#include "Node.h"
#include "RO.h"
#include "PRG.h"
#include "H_SHA.h"
#include "ElGamal.h"
#include "Utilities.h"

#include "Debug.h"

bool DecryptionFactorsVerifier(const int j, const proofStruct &ps, const Node &f, const Node &tauDec, const Node &sigmaDec, const Node &w) {

    
    //Step 1
    for(unsigned int i=0; i<ps.lambda; ++i)
    {
	    // a)
	    Node tauDeci = tauDec.getNodeChild(i);

	    IntLeaf y_prime = tauDeci.getIntLeafChild(0);
        Node B_prime;
        if(ps.width == 1) {
            B_prime.addChild(tauDeci.getNodeChild(1));
        } else {
            B_prime = tauDeci.getNodeChild(1);
        }

	    if(!isElemOfGq(ps.Gq, y_prime) ||
	       !isElemOfMw(ps, B_prime)) 
	    {
	        return false;
	    }
    
	    // b)
	    IntLeaf sigmaDeci = sigmaDec.getIntLeafChild(i);
	
	    if(!isElemOfZn(ps.Gq.getIntLeafChild(0), sigmaDeci))
	    {
	        return false;
	    }
    }

	//Step 2
	//Construct seed
	Node seed, seed_a, seed_b;
	seed_a.addChild(ps.Gq.getIntLeafChild(2));
	seed_a.addChild(w);
	seed_b.addChild(ps.y);
	seed_b.addChild(f);
	seed.addChild(seed_a);
	seed.addChild(seed_b);

	bytevector seed_data = ps.rho;
	bytevector seed_data2 = seed.serialize();
	seed_data.insert(seed_data.end(), seed_data2.begin(), seed_data2.end());

    RO RO_seed(ps.hash, ps.nH);
    IntLeaf s = RO_seed(seed_data);

    

    //TODO: sdata blir fel!
    print_debug("DecryptionFactorsVerifier: s", s.toVector());

	//Step 3
	PRG prg(H_SHA256, s.toVector(), ps.nH);
	Node t;
	for (unsigned int i = 0; i < ps.N; i++)
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

	bytevector challenge_data = ps.rho;
	bytevector challenge_data2 = challenge.serialize();
	challenge_data.insert(challenge_data.end(), challenge_data2.begin(), challenge_data2.end());

	RO RO_challenge(ps.hash, ps.nV);
	IntLeaf v = RO_challenge(challenge_data);

	print_debug("DecryptionFactorsVerifier: v", v.toVector());

	//Step 5
	IntLeaf p = ps.Gq.getIntLeafChild(0);
	Node u = w.getChildren(0);
	Node yPrime = tauDec.getChildren(0);
	IntLeaf A = u.expMultMod(e, p);
	
	print_debug("DecryptionFactorsVerifier: u", u.serializeString());
	print_debug("DecryptionFactorsVerifier: A", A.serializeString());
	print_debug("DecryptionFactorsVerifier: yp", yPrime.serializeString());

	if(j == 0) {

		Node Bnode;
		for (int i = 0; i < f.getLength(); i++)
		{
			Bnode.addChild(f.getChildren(i).prodMod(p));
		}
		IntLeaf B = Bnode.expMultMod(e, p);
		
		IntLeaf x = sigmaDec.sumMod(p);

		IntLeaf cond1left = ps.pk.prodMod(p).expMod(v, p) * yPrime.prodMod(p);
		IntLeaf cond1right = ps.Gq.getIntLeafChild(2).expMod(x, p);

		IntLeaf cond2left = B.expMod(v, p) * tauDec.getChildren(1).prodMod(p);
		IntLeaf cond2right = PDec(x, A, p);

		
		print_debug("DecryptionFactorsVerifier. B", B.serializeString());

		return cond1left == cond1right && cond2left == cond2right;
	} else {
		IntLeaf Bj = f.getChildren(j).expMultMod(e, p);

		IntLeaf x = sigmaDec.getIntLeafChild(j);

		IntLeaf cond1left = ps.pk.getIntLeafChild(j).expMod(v, p) * yPrime.getIntLeafChild(j);
		IntLeaf cond1right = ps.Gq.getIntLeafChild(2).expMod(x, p);

		IntLeaf cond2left = Bj.expMod(v, p) * tauDec.getIntLeafChild(j);
		IntLeaf cond2right = PDec(x, A, p);

		print_debug("DecryptionFactorsVerifier: B",j,Bj.serialize());

		return cond1left == cond1right && cond2left == cond2right;
	}

	return true;
}
