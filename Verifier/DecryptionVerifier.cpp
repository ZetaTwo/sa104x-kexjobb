#include "DecryptionVerifier.h"
#include "DecryptionFactorsVerifier.h"

#include "ProofOfShuffle.h"
#include "ElGamal.h"

#include "Node.h"
#include "FileNames.h"

#include "Debug.h"


bool DecryptionVerifier(const proofStruct &ps, const Node L, const Node m) {

    IntLeaf p = ps.Gq.getIntLeafChild(0);

	//Step 1
    Node f, tauDec, sigmaDec;
    try 
    {
	for (unsigned int l = 1; l <= ps.lambda; l++)
	{
	    char filename[FILENAME_BUFFER_SIZE];
	    sprintf(filename, DECRYPTION_FACTORS_FILE_TMPL.c_str(), l);
	    Node f_l = Node(ps.directory + "/proofs/" + filename);
	    f.addChild(f_l);

	    sprintf(filename, DECR_FACT_COMMITMENT_FILE_TMPL.c_str(), l);
	    Node tauDec_l = Node(ps.directory + "/proofs/" + filename);
	    tauDec.addChild(tauDec_l);

	    sprintf(filename, DECR_FACT_REPLY_FILE_TMPL.c_str(), l);
	    std::ifstream sigmaDec_l_file((ps.directory + "/proofs/" + filename).c_str(), std::fstream::in | std::fstream::binary);
	    IntLeaf sigmaDec_l = IntLeaf(sigmaDec_l_file);
	    sigmaDec.addChild(sigmaDec_l);
    
	    print_debug("DecryptionVerifier: f", l, f_l.serialize());
	}
    }
    catch(...)
    {
	return false;
    }
    


    //Step 2
    bool result = DecryptionFactorsVerifier(0, ps, f, tauDec, sigmaDec, L);

    if(!result) {
	//Step 3
	for (int l = 0; l < f.getLength(); l++)
	{
	    result = DecryptionFactorsVerifier(l+1, ps, f, tauDec, sigmaDec, L);

	    IntLeaf xL = ps.x.getIntLeafChild(l);
			

	    if(!result && (xL == BOTTOM || f.getIntLeafChild(l) != PDec(xL, L.getIntLeafChild(l), p))) {
		return false;
	    }
	}
    }

    //Step 4
    IntLeaf x = f.prod();
    for(int i = 0; i < L.getLength(); i++) {
	if(m.getIntLeafChild(i) != TDec(L.getIntLeafChild(i), x, p)) {
	    return false;
	}
    }

    return true;
}
