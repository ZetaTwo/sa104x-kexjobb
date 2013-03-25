#include <fstream>
#include <string>

#include "Node.h"
#include "IntLeaf.h"
#include "ShufflingVerifier.h"
#include "ProofOfShuffle.h"
#include "Utilities.h"
#include "FileNames.h"

bool verifyShuffling(proofStruct &pfStr,
		     int lambda, 
		     Node &L0, 
		     Node &Llambda, 
		     bool posc, 
		     bool ccpos)
{
    std::ifstream fstr("maxciph", std::fstream::in);
    
    // maxciph does not exist
    if(!fstr)
    {
	Node L_array = Node();	
	L_array.addChild(L0);
	Node Llast = L0;

	for(int l=1; l<=lambda; l++)
	{
	    Node L;

	    // Step 1
	    if(l < lambda)
	    {
		const std::string cipher_text_file_name = 
		    CIPHERTEXTS_FILE_PREFIX + std::to_string(l) + std::string(".bt");
		
		std::ifstream ciphtext_stream(cipher_text_file_name, std::fstream::in);
		
		if(!ciphtext_stream)
		    return false;

		L = Node(ciphtext_stream);

		if(!isListOfCiphertexts(pfStr, L))
		    return false;

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
		mu = Node("PermutationCommitment<" + std::to_string(l) + ">.bt");
		tau_pos = Node("PoSCommitment<" + std::to_string(l) + ">.bt");
		sigma_pos = Node("PoSReply<" + std::to_string(l) + ">.bt");
	    }
	    catch(...)
	    {
		return false;
	    }


	    //Step 2
	    // Verify proof of shuffle
	    // Execute Algorithm 19 with specified input
	    if(!proofOfShuffle(pfStr, Llast, L, mu, tau_pos, sigma_pos) &&
	       L_array.getNodeChild(l) != L_array.getNodeChild(l-1))
		return false;

	    Llast = L;
	}

	// Step 3
	return true;

    }
    // If maxciph file exists
    else
    {
	return true;
    }
}



bool isListOfCiphertexts(const proofStruct &pfStr, Node &L)
{
    try {
	for(unsigned int i=0; i<pfStr.N; ++i)
	{
	    if(!isElemOfCw(pfStr, L.getNodeChild(i)))
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
