#include "ProofOfShuffle.h"

#include "PRG.h"
#include "RO.h"
#include "ElGamal.h"
#include "RandomArray.h"
#include "DataLeaf.h"

#include <cmath>

bool proofOfShuffle(proofStruct &pfStr,
		    const Node &w,
		    const Node &w_prime,
		    const Node &mu,
		    const Node &tau_pos,
		    const Node &sigma_pos)
{
    Node u;

    IntLeaf A_prime;
    IntLeaf C_prime;
    IntLeaf D_prime;

    Node F_prime;

    Node B;
    Node B_prime;

    IntLeaf kA;
    IntLeaf kC;
    IntLeaf kD;
    IntLeaf kF;

    Node kB;
    Node kE;
    
    const IntLeaf &p = pfStr.Gq.getIntLeafChild(0);
    const IntLeaf &q = pfStr.Gq.getIntLeafChild(1);
    const IntLeaf &g = pfStr.Gq.getIntLeafChild(2);

    // Step 1

    // a) assert that mu is array of Pdersen commitments in pfStr.Gq
    
    try
    {
	u = mu;

	for(unsigned int i=0; i < pfStr.N; ++i)
	{
	    if(!isPedersenCommitment(pfStr.Gq, u.getIntLeafChild(i)))
	    {
		return false;
	    }
	}
    }
    catch(...)
    {
	return false;
    }

    // b) assert that tau_pos is a Node (B, A', B', C', D', F'), where
    // A',C',D' is in G_q, F' is in Cw and B and B' are arrays of N
    // elements in Gq

    try
    {
	A_prime = tau_pos.getIntLeafChild(1);
	C_prime = tau_pos.getIntLeafChild(3);
	D_prime = tau_pos.getIntLeafChild(4);

	if(!isElemOfGq(pfStr.Gq, A_prime) ||
	   !isElemOfGq(pfStr.Gq, C_prime) ||
	   !isElemOfGq(pfStr.Gq, D_prime))
	{
	    return false;
	}
	
	F_prime = tau_pos.getNodeChild(5);
	if(!isElemOfCw(pfStr, F_prime))
	{
	    return false;
	}

	B = tau_pos.getNodeChild(0);
	B_prime = tau_pos.getNodeChild(2);

	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    if(!isElemOfGq(pfStr.Gq, B.getIntLeafChild(i)) ||
	       !isElemOfGq(pfStr.Gq, B_prime.getIntLeafChild(i)))
	    {
		return false;
	    }
	}
    }
    catch(...)
    {
	return false;
    }

    // c) assert that sigma_pos is a Node (kA, kB, kC, kD, kE, kF),
    // where kA, kC, kD, kF is in Z_q, kB is an array of N elements in
    // Rw and kE is an array of N elements in G_q

    try
    {
        kA = sigma_pos.getIntLeafChild(0);
        kC = sigma_pos.getIntLeafChild(2);
        kD = sigma_pos.getIntLeafChild(3);
	kF = sigma_pos.getIntLeafChild(5);

	kB = sigma_pos.getNodeChild(1);
	kE = sigma_pos.getNodeChild(4);

	if(!isElemOfZn(q, kA) ||
	   !isElemOfZn(q, kC) ||
	   !isElemOfZn(q, kD) ||
	   !isElemOfZn(q, kF))
	{
	    return false;
	}

	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    if(!isElemOfRw(kB.getChild(i)))
	    { 
		return false;
	    }

	    if(!isElemOfZn(q, kE.getIntLeafChild(i)))
	    {
		return false;
	    }
	}

    }
    catch(...)
    {
	return false;
    }

    // Get random array
    DataLeaf generators = DataLeaf("generators");
    RO r = RO(pfStr.hash, pfStr.nHash);
    IntLeaf s = r(pfStr.rho.concatData(&generators));

    Node h = RandomArray(pfStr.Gq, pfStr.N, pfStr.hash, s.serialize(), pfStr.nR);

    // Step 2, compute a seed
    Node seed_gen;
    seed_gen.addChild(g); // add g, generator of Gq
    seed_gen.addChild(h);
    seed_gen.addChild(u);
    seed_gen.addChild(pfStr.pk);
    seed_gen.addChild(w); 
    seed_gen.addChild(w_prime);

    bytevector gen = pfStr.rho.concatData(&seed_gen);
		

    RO rs = RO(pfStr.hash, (pfStr.nE/8)*8);

    IntLeaf seed = rs(gen);

    // Step 3

    PRG prg = PRG(pfStr.hash, seed.serialize(), pfStr.nE);

    Node t;    
    for(unsigned int i=0; i<pfStr.N; ++i)
    {
	t.addChild(prg.next());
    }

    IntLeaf exp(2);
    exp.expTo(pfStr.nE);

    Node e = t.mod(exp);

    IntLeaf A = u.expMultMod(e, p);
    

    Node F;

    F.addChild(w.getChildren(0).expMultMod(e, p));
    F.addChild(w.getChildren(1).expMultMod(e, p));

    // Step 4, compute a challenge
    Node challenge_gen;
    challenge_gen.addChild(seed);
    challenge_gen.addChild(tau_pos);

    gen = pfStr.rho.concatData(&challenge_gen);

    RO rc = RO(pfStr.hash, std::pow(2,pfStr.nV));

    IntLeaf v = rc(gen);

    // Step 5
    IntLeaf C = u.prodMod(p) * h.prodMod(p).inverse(p);

    IntLeaf D = B.getIntLeafChild(pfStr.N - 1) * h.getIntLeafChild(0).expMod(e.prodMod(p), p).inverse(p);
    
    if(A.expMod(v, p)*A_prime != g.expMod(kA, p)*h.expMultMod(kE, p))
    {
	return false;
    }

    // Handling case: B.getChild(i-1) = h_0
    if(B.getIntLeafChild(0).expMod(v,p) * B_prime.getIntLeafChild(0) != 
       g.expMod(kB.getIntLeafChild(0),p) * h.getIntLeafChild(0).expMod(kE.getIntLeafChild(0),p))
    {
	return false;
    }

    for(unsigned int i=1; i<pfStr.N; ++i)
    {
	if(B.getIntLeafChild(i).expMod(v, p) * B_prime.getIntLeafChild(i) !=
	   g.expMod(kB.getIntLeafChild(i),p) * B.getIntLeafChild(i-1).expMod(kE.getIntLeafChild(i),p))
	{
	    return false;
	}
    }

    if(C.expMod(v, p)*C_prime != g.expMod(kC, p))
    {
	return false;
    }

    if(D.expMod(v, p)*D_prime != g.expMod(kD, p))
    {
	return false;
    }

    if(F.expMod(v, p) * F_prime != Enc(pfStr.pk, IntLeaf(1), -kF, p) * w_prime.expMultMod(kE, p))
    {
	return false;
    }


    return true;
} 

