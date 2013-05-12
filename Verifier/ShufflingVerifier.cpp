#include <fstream>
#include <string>

#include "Node.h"
#include "IntLeaf.h"
#include "ShufflingVerifier.h"
#include "ProofOfShuffle.h"
#include "Utilities.h"
#include "FileNames.h"

#include "Debug.h"

bool verifyShuffling(proofStruct &pfStr,
                     Node &L0, 
                     Node &Llambda, 
                     bool posc, 
                     bool ccpos)
{
    std::ifstream fstr("maxciph", std::fstream::in | std::fstream::binary);

    // maxciph does not exist
    if(!fstr)
    {
        Node L_array;	
        L_array.addChild(L0);
        Node Llast = L0;

        for(unsigned int l=1; l<=pfStr.lambda; l++)
        {
            Node L;

            // Step 1 - if l < lambda, read array L_l with N ciphertexts
            if(l < pfStr.lambda)
            {	
                char ciphertexts_filename[FILENAME_BUFFER_SIZE];
                sprintf(ciphertexts_filename, CIPHERTEXTS_FILE_TMPL.c_str(), l);

                std::ifstream ciphtext_stream((pfStr.directory + "/proofs/" + ciphertexts_filename).c_str(), std::fstream::in | std::fstream::binary);

                if(!ciphtext_stream) {
                    return false;
                }
		try 
		{
		    L = Node(ciphtext_stream);
		}
		catch(...)
		{
		    return false;
		}

                //TODO: Repair for width > 1
                if(!isListOfCiphertexts(pfStr, L)) {
                    return false;
                }

                L_array.addChild(L);
            }
            else
            {
                L_array.addChild(Llambda);
            }


            Node mu;
            Node tau_pos;
            Node sigma_pos;


            try
            {
                char filename[FILENAME_BUFFER_SIZE];

                sprintf(filename, PERMUTATION_COMMIMENTS_FILE_TMPL.c_str(), l);	
                mu = Node(pfStr.directory + "/proofs/" + filename);

                sprintf(filename, POS_COMMITMENT_FILE_TMPL.c_str(), l);	
                tau_pos = Node(pfStr.directory + "/proofs/" + filename);

                sprintf(filename, POS_REPLY_FILE_TMPL.c_str(), l);	
                sigma_pos = Node(pfStr.directory + "/proofs/" + filename);
            }
            catch(...)
            {
                return false;
            }


            //Step 2
            // Verify proof of shuffle
            // Execute Algorithm 19 with specified input
	    print_debug("BEGIN PARTY", l);

            if(!proofOfShuffle(pfStr, Llast, L, mu, tau_pos, sigma_pos) &&
                L_array.getNodeChild(l) != L_array.getNodeChild(l-1))
                return false;

	    print_debug("END PARTY", l);

            Llast = L;
        }

        // Step 3
        return true;

    }
    // If maxciph file exists
    else
    {
        return false;
    }
}



bool isListOfCiphertexts(const proofStruct &pfStr, Node &L) {

    try {
        for(int i = 0; i < L.getLength(); ++i)
        {
            Node u;
            Node v;
            if(pfStr.width == 1) {
                u.addChild(L.getNodeChild(0).getIntLeafChild(i));
                v.addChild(L.getNodeChild(1).getIntLeafChild(i));
            } else {
                u = L.getNodeChild(0).getNodeChild(i);
                v = L.getNodeChild(1).getNodeChild(i);
            }

            Node uv;
            uv.addChild(u);
            uv.addChild(v);
            if(!isElemOfCw(pfStr, uv))
            {
                return false;
            }
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}
