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
    
    const IntLeaf &p = static_cast<const IntLeaf &>(pfStr.Gq->getChild(0));
    const IntLeaf &q = static_cast<const IntLeaf &>(pfStr.Gq->getChild(1));
    const IntLeaf &g = static_cast<const IntLeaf &>(pfStr.Gq->getChild(2));

    // Step 1

    // a) assert that pfStr->mu is array of Pdersen commitments in pfStr->Gq
    
    try
    {
	u = *pfStr.mu;

	for(unsigned int i=0; i < pfStr.N; ++i)
	{
	    if(!isPedersenCommitment(*pfStr.Gq, 
				     static_cast<const IntLeaf &>(u.getChild(i))))
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
	A_prime = static_cast<const IntLeaf &>(tau_pos.getChild(1));
	C_prime = static_cast<const IntLeaf &>(tau_pos.getChild(3));
	D_prime = static_cast<const IntLeaf &>(tau_pos.getChild(4));

	if(!isElemOf(*pfStr.Gq, A_prime) ||
	   !isElemOf(*pfStr.Gq, C_prime) ||
	   !isElemOf(*pfStr.Gq, D_prime))
	{
	    return false;
	}
	
	F_prime = static_cast<const Node &>(tau_pos.getChild(5));
	if(!isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(F_prime.getChild(0))) ||
	   !isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(F_prime.getChild(1))))
	{
	    return false;
	}

	B = static_cast<const Node &>(tau_pos.getChild(0));
	B_prime = static_cast<const Node &>(tau_pos.getChild(2));

	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    if(!isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(B.getChild(i))) ||
	       !isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(B_prime.getChild(i))))
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
        kA = static_cast<const IntLeaf &>(sigma_pos.getChild(0));
        kC = static_cast<const IntLeaf &>(sigma_pos.getChild(2));
        kD = static_cast<const IntLeaf &>(sigma_pos.getChild(3));
	kF = static_cast<const IntLeaf &>(sigma_pos.getChild(5));

	kB = static_cast<const Node &>(sigma_pos.getChild(1));
	kE = static_cast<const Node &>(sigma_pos.getChild(4));

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

	    if(!isElemOf(q, static_cast<const IntLeaf &>(kE.getChild(i))))
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

    PRG prg = PRG(pfStr.hash, seed.toVector());

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

    IntLeaf D = static_cast<const IntLeaf &>(B.getChild(pfStr.N - 1)) * static_cast<const IntLeaf &>(h.getChild(0)).expMod(e.prodMod(p), p).inverse(p);
    
    if(A.expMod(v, p)*A_prime != g.expMod(kA, p)*h.expMultMod(kE, p))
    {
	return false;
    }

    // Handling case: B.getChild(i-1) = h_0
    if(static_cast<const IntLeaf &>(B.getChild(0)).expMod(v,p) * static_cast<const IntLeaf &>(B_prime.getChild(0)) != 
       g.expMod(static_cast<const IntLeaf &>(kB.getChild(0)),p)*
       static_cast<const IntLeaf &>(h.getChild(0)).expMod(static_cast<const IntLeaf &>(kE.getChild(0)),p))
    {
	return false;
    }

    for(unsigned int i=1; i<pfStr.N; ++i)
    {
	if(static_cast<const IntLeaf &>(B.getChild(i)).expMod(v, p) * static_cast<const IntLeaf &>(B_prime.getChild(i)) !=
	   g.expMod(static_cast<const IntLeaf &>(kB.getChild(i)),p) * 
	   static_cast<const IntLeaf &>(B.getChild(i-1)).expMod(static_cast<const IntLeaf &>(kE.getChild(i)),p))
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

    if(F.expMod(v, p) * F_prime != Enc(*pfStr.pk, IntLeaf(1), -kF, g, p) * pfStr.w_prime->expMultMod(kE, p))
    {
	return false;
    }


    return true;
} 

