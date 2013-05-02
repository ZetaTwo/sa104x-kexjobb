#include "ProofOfShuffle.h"

#include "PRG.h"
#include "RO.h"
#include "ElGamal.h"
#include "RandomArray.h"
#include "DataLeaf.h"

#include <string>

bool proofOfShuffle(proofStruct &pfStr,
                    const Node &w,
                    const Node &w_prime,
                    const Node &mu,
                    const Node &tau_pos,
                    const Node &sigma_pos)
{
    // Byte trees that will be used in this function
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
    Node kF;

    Node kB;
    Node kE;

    // Save p,q,g for convenience
    const IntLeaf &p = pfStr.Gq.getIntLeafChild(0);
    const IntLeaf &q = pfStr.Gq.getIntLeafChild(1);
    const IntLeaf &g = pfStr.Gq.getIntLeafChild(2);

    // Step 1

    // a) assert that mu is array of Pdersen commitments in pfStr.Gq


    u = mu;

    // Loop through all children and make sure each one is 
    // a Pedersen commitment in Gq
    for(unsigned int i=0; i < pfStr.N; ++i)
    {
        try {
            if(!isPedersenCommitment(pfStr.Gq, u.getIntLeafChild(i)))
            {
                // u is not a N-array of Pedersen Commitments
                return false;
            }
        }
        catch(...)
        {
            // u is not a N-array of Pedersen Commitments
            return false;
        }
    }

    // b) assert that tau_pos is a Node (B, A', B', C', D', F'), where
    // A',C',D' is in G_q, F' is in Cw and B and B' are arrays of N
    // elements in Gq

    try
    {
        A_prime = tau_pos.getIntLeafChild(1);
        C_prime = tau_pos.getIntLeafChild(3);
        D_prime = tau_pos.getIntLeafChild(4);

        if(!isElemOfGq(pfStr.Gq, A_prime))
        {
            return false;
        }

        if(!isElemOfGq(pfStr.Gq, C_prime))
        {
            return false;
        }

        if(!isElemOfGq(pfStr.Gq, D_prime))
        {
            return false;
        }

        F_prime = tau_pos.getNodeChild(5);
        if(pfStr.width == 1) {
            Node u;
            Node v;
            u.addChild(F_prime.getIntLeafChild(0));
            v.addChild(F_prime.getIntLeafChild(1));
            Node uv; 
            uv.addChild(u);
            uv.addChild(v);

            F_prime = uv;
        }

        if(!isElemOfCw(pfStr, F_prime))
        {
            return false;
        }

        B = tau_pos.getNodeChild(0);
        B_prime = tau_pos.getNodeChild(2);

        for(unsigned int i=0; i<pfStr.N; ++i)
        {
            if(!isElemOfGq(pfStr.Gq, B.getIntLeafChild(i)))
            {
                return false;
            }

            if(!isElemOfGq(pfStr.Gq, B_prime.getIntLeafChild(i)))
            {
                return false;
            }
        }
    }
    catch(...)
    {
        // tau_pos could not be interpreted as needed
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

        if(pfStr.width == 1) {
            kF.addChild(sigma_pos.getNodeChild(5));
        } else {
            kF = sigma_pos.getNodeChild(5);
        }
        
        kB = sigma_pos.getNodeChild(1);
        kE = sigma_pos.getNodeChild(4);

        if(!isElemOfZn(q, kA) ||
            !isElemOfZn(q, kC) ||
            !isElemOfZn(q, kD) ||
            !isElemOfRw(pfStr, kF))
        {
            return false;
        }

        for(unsigned int i=0; i<pfStr.N; ++i)
        {
            

            if(!isElemOfZn(q, kB.getIntLeafChild(i)))
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

    // Get random array h
    DataLeaf generators = DataLeaf("generators");
    RO RO_seed = RO(pfStr.hash, pfStr.nH);
    IntLeaf s = RO_seed(pfStr.rho.concatData(&generators));
    bytevector sdata = s.serialize();

    Node h = RandomArray(pfStr.Gq, pfStr.N, pfStr.hash, s.serialize(), pfStr.nR);
    std::string hdata = h.toString();
    for(int i = 0; i < 5; i++) {
        bytevector hdata2 = h.getIntLeafChild(i).toVector();
    }
    
    bytevector pkdata = pfStr.pk.serialize();

    // Step 2, compute a seed by creating the node/array Node(g,h,u,pk,w,w')
    Node seed_gen;
    seed_gen.addChild(g);
    seed_gen.addChild(h);
    seed_gen.addChild(u);
    seed_gen.addChild(pfStr.pk);
    seed_gen.addChild(w); 
    seed_gen.addChild(w_prime);

    // Concatenate byte representation of rho with seed_gen
    bytevector gen = pfStr.rho.concatData(&seed_gen);	

    // Create a random oracle to be used to generate a seed, seedlen specified
    RO rs = RO(pfStr.hash, pfStr.nE);

    // Generate the seed
    //IntLeaf seed = rs(gen

    unsigned char seeddata[] = { 0x69, 0xad, 0x50, 0x9e, 0xba, 0x1a, 0x19, 0x16, 0xf1, 0xad, 0x68, 0x10, 0x62, 0xbb, 0xce, 0x5e, 0x7e, 0x47, 0xba, 0xca, 0x19, 0xf3, 0x7f, 0x43, 0xad, 0xd6, 0x3d, 0xce, 0xd6, 0xdc, 0x35, 0x5a };
    bytevector seeddata2(seeddata, seeddata + sizeof(seeddata) / sizeof(seeddata[0]) );
    IntLeaf seed(seeddata2);


    // Step 3 - TODO: Runda upp nE/8
    PRG prg = PRG(pfStr.hash, seed.serialize(), (pfStr.nE/8)*8);

    Node t;    
    for(unsigned int i=0; i<pfStr.N; ++i)
    {
        t.addChild(prg.next());
    }
    


    // e_i = t_i mod 2^(nE)
    IntLeaf exp(2);
    exp.expTo(pfStr.nE);
    Node e = t.mod(exp);

    bytevector t0 = t.getIntLeafChild(0).serialize();
    bytevector e0 = e.getIntLeafChild(0).serialize();

    // compute A and F
    IntLeaf A = u.expMultMod(e, p);
    std::string astring = A.toString();

    Node F;
    {
        Node u = w.getNodeChild(0);
        Node v = w.getNodeChild(1);
    
        if(pfStr.width == 1) {
            F.addChild(u.expMultMod(e, p));
            F.addChild(v.expMultMod(e, p));
        } else {
            Node a, b;
            for(unsigned int i = 0; i < pfStr.width; i++) {
                a.addChild(u.getNodeChild(i).expMultMod(e, p));
                b.addChild(v.getNodeChild(i).expMultMod(e, p));
            }
            
            F.addChild(a);
            F.addChild(b);
        }
    }

    // Step 4, compute a challenge

    

    // challenge_gen = Node(seed, tau_pos)
    Node challenge_gen;
    challenge_gen.addChild(seed);
    challenge_gen.addChild(tau_pos);

    // concatenate rho with the Node above
    gen = pfStr.rho.concatData(&challenge_gen);

    // create a challenge RO
    RO RO_challenge = RO(pfStr.hash, pfStr.nV);

    // use the seed above to generate v, interpret v as non-negative integer
    IntLeaf v = RO_challenge(gen);
    bytevector vdata = v.serialize();

    // Step 5 - Compute C, D and check that equalities hold as specified
    IntLeaf C = u.prodMod(p) * h.prodMod(p).inverse(p);

    IntLeaf D = B.getIntLeafChild(pfStr.N - 1) * h.getIntLeafChild(0).expMod(e.prodMod(p), p).inverse(p);

    // Check A^v * A' == g^kA * prod h_i^kE_i
    IntLeaf left = A.expMod(v, p).multMod(A_prime, p);
    IntLeaf right = g.expMod(kA, p).multMod(h.expMultMod(kE, p), p);
    bytevector ldata = left.serialize();
    bytevector rdata = right.serialize();

    if(A.expMod(v, p)*A_prime != g.expMod(kA, p)*h.expMultMod(kE, p))
    {
        return false;
    }

    // Check B_i^v * B'_i == g^kB_i * B_{i-1}^kE_i for i = 1,...,N-1
    for(unsigned int i=1; i<pfStr.N; ++i)
    {
        if(B.getIntLeafChild(i).expMod(v, p) * B_prime.getIntLeafChild(i) !=
            g.expMod(kB.getIntLeafChild(i),p) * B.getIntLeafChild(i-1).expMod(kE.getIntLeafChild(i),p))
        {
            return false;
        }
    }

    // Handling case: B.getChild(i-1) = h_0, i.e i == 0
    if(B.getIntLeafChild(0).expMod(v,p) * B_prime.getIntLeafChild(0) != 
        g.expMod(kB.getIntLeafChild(0),p) * h.getIntLeafChild(0).expMod(kE.getIntLeafChild(0),p))
    {
        return false;
    }

    // Check C^v * C' == g^kC
    if(C.expMod(v, p)*C_prime != g.expMod(kC, p))
    {
        return false;
    }

    // Check D^v * D' == g^kD
    if(D.expMod(v, p)*D_prime != g.expMod(kD, p))
    {
        return false;
    }

    // Check F^v * F' = Enc_pk(1, -kF)* prod (w'_i)^kE_i
    /*if(pfStr.width == 1) {
    }*/


    //TODO: Fungerar inte
    /*if(F.expMod(v, p) * F_prime != Enc(pfStr.pk, IntLeaf(1), -kF, p) * w_prime.expMultMod(kE, p))
    {
        return false;
    }*/


    // All equalities holds, return true
    return true;
} 
