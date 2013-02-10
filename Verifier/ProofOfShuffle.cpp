#include "ProofOfShuffle.h"

bool proofOfShuffle(proofStruct &pfStr, const Node &tau_pos, const Node &sigma_pos)
{
    // Step 1

    // a) assert that pfStr->mu is array of Pdersen commitments in pfStr->Gq
    
    try
    {
	for(unsigned int i=0; i < pfStr.N; ++i)
	{
	    if(!isPedersenCommitment(*pfStr.Gq, 
				     static_cast<const IntLeaf &>(pfStr.mu->getChild(i))))
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
	if(!isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(tau_pos.getChild(1))) ||
	   !isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(tau_pos.getChild(3))) ||
	   !isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(tau_pos.getChild(4))))
	{
	    return false;
	}
	
	Node Fprime = static_cast<const Node &>(tau_pos.getChild(5));
	if(!isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(Fprime.getChild(0))) ||
	   !isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(Fprime.getChild(1))))
	{
	    return false;
	}

	Node B = static_cast<const Node &>(tau_pos.getChild(0));
	Node Bprime = static_cast<const Node &>(tau_pos.getChild(2));

	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    if(!isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(B.getChild(i))) ||
	       !isElemOf(*pfStr.Gq, static_cast<const IntLeaf &>(Bprime.getChild(i))))
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
	const IntLeaf &kA = static_cast<const IntLeaf &>(sigma_pos.getChild(0));
	const IntLeaf &kC = static_cast<const IntLeaf &>(sigma_pos.getChild(2));
	const IntLeaf &kD = static_cast<const IntLeaf &>(sigma_pos.getChild(3));
	const IntLeaf &kF = static_cast<const IntLeaf &>(sigma_pos.getChild(5));

	const Node &kB = static_cast<const Node &>(sigma_pos.getChild(1));
	const Node &kE = static_cast<const Node &>(sigma_pos.getChild(4));

	const IntLeaf &q = static_cast<const IntLeaf &>(pfStr.Gq->getChild(1));

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



    // Step 2, compute a seed
    Node seed_gen;
    seed_gen.addChild(pfStr.Gq->getChild(2)); // add g, generator of Gq
    /* generator.addChild(h) add h? */
    seed_gen.addChild(*pfStr.mu); // add u vector
    seed_gen.addChild(*pfStr.pk); // add public key
    seed_gen.addChild(*pfStr.w); 
    seed_gen.addChild(*pfStr.w_prime);

    /* IntLeaf seed = RO_seed(*pfStr.rho, seed_gen); */

    // Step 3
    Node t;/* = PRG(seed); */

    IntLeaf exp(2);
    exp.expTo(pfStr.nE);

    Node e = t.mod(exp);

    const IntLeaf &p = static_cast<const IntLeaf &>(pfStr.Gq->getChild(0));
    IntLeaf A = pfStr.mu->expMultMod(e, p);
    IntLeaf F = pfStr.w->expMultMod(e, p);

    // Step 4, compute a challenge
    Node challenge_gen;
    challenge_gen.addChild(seed);
    challenge_gen.addChild(tau_pos);

    IntLeaf v; /* RO_challenge(*pfStr.rho, challenge_gen); */

    // Step 5
    // C = pfStr.mu->prodMod(p);
    // Includes division?		  

    return true;
} 
