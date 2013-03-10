#include "ProofOfShuffle.h"

#include "PRG.h"
#include "RO.h"
#include "ElGamal.h"

#include <cmath>

bool proofOfShuffle(proofStruct &pfStr, const Node &tau_pos, const Node &sigma_pos)
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
    
    const IntLeaf &p = pfStr.Gq->getIntLeafChild(0);
    const IntLeaf &q = pfStr.Gq->getIntLeafChild(1);
    const IntLeaf &g = pfStr.Gq->getIntLeafChild(2);

    // Step 1

    // a) assert that pfStr->mu is array of Pdersen commitments in pfStr->Gq
    
    try
    {
	u = *pfStr.mu;

	for(unsigned int i=0; i < pfStr.N; ++i)
	{
	    if(!isPedersenCommitment(*pfStr.Gq, u.getIntLeafChild(i)))
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

	if(!isElemOf(*pfStr.Gq, A_prime) ||
	   !isElemOf(*pfStr.Gq, C_prime) ||
	   !isElemOf(*pfStr.Gq, D_prime))
	{
	    return false;
	}
	
	F_prime = tau_pos.getNodeChild(5);
	if(!isElemOf(*pfStr.Gq, F_prime.getIntLeafChild(0)) ||
	   !isElemOf(*pfStr.Gq, F_prime.getIntLeafChild(1)))
	{
	    return false;
	}

	B = tau_pos.getNodeChild(0);
	B_prime = tau_pos.getNodeChild(2);

	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    if(!isElemOf(*pfStr.Gq, B.getIntLeafChild(i)) ||
	       !isElemOf(*pfStr.Gq, B_prime.getIntLeafChild(i)))
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

	if(!isElemOf(q, kA) ||
	   !isElemOf(q, kC) ||
	   !isElemOf(q, kD) ||
	   !isElemOf(q, kF))
	{
	    return false;
	}

	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    // if kB.getChild(i) is not elem of Rw
	    // return false

	    if(!isElemOf(q, kE.getIntLeafChild(i)))
	    {
		return false;
	    }
	}

    }
    catch(...)
    {
	return false;
    }

    Node h; // = calles_metod();

    // Step 2, compute a seed
    Node seed_gen;
    seed_gen.addChild(g); // add g, generator of Gq
    seed_gen.addChild(h);
    seed_gen.addChild(u);
    seed_gen.addChild(*pfStr.pk);
    seed_gen.addChild(*pfStr.w); 
    seed_gen.addChild(*pfStr.w_prime);


    std::vector<unsigned char> gen = pfStr.rho->toVector();
    std::vector<unsigned char> seed_gen_vec = seed_gen.toVector();
    gen.insert(gen.end(), seed_gen_vec.begin(), seed_gen_vec.end());

    RO rs = RO(pfStr.hash, (pfStr.nE/8)*8);

    IntLeaf seed = rs(gen);

    // Step 3

    PRG prg = PRG(pfStr.hash, seed.toVector(), pfStr.nE);

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

    F.addChild(pfStr.w->getChildren(0).expMultMod(e, p));
    F.addChild(pfStr.w->getChildren(1).expMultMod(e, p));

    // Step 4, compute a challenge
    Node challenge_gen;
    challenge_gen.addChild(seed);
    challenge_gen.addChild(tau_pos);

    gen = pfStr.rho->toVector();
    std::vector<unsigned char> chal_gen_vec = challenge_gen.toVector();
    gen.insert(gen.end(), chal_gen_vec.begin(), chal_gen_vec.end());


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

    if(F.expMod(v, p) * F_prime != Enc(*pfStr.pk, IntLeaf(1), -kF, p) * pfStr.w_prime->expMultMod(kE, p))
    {
	return false;
    }


    return true;
} 

