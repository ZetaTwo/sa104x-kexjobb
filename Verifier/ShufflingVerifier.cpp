#include <fstream>
#include <string>

#include "Node.h"
#include "IntLeaf.h"
#include "ShufflingVerifier.h"
#include "ProofOfShuffle.h"
#include "Utilities.h"
#include "FileNames.h"


bool verifyShuffling(proofStruct &pfStr,
		     Node &L0, 
		     Node &Llambda, 
		     bool posc, 
		     bool ccpos)
{
    std::ifstream fstr("maxciph", std::fstream::in);
    
    // maxciph does not exist
    if(!fstr)
    {
	Node L_array;	
	L_array.addChild(L0);
	Node Llast = L0;

	for(int l=1; l<=pfStr.lambda; l++)
	{
	    Node L;

	    // Step 1 - if l < lambda, read array L_l with N ciphertexts
	    if(l < pfStr.lambda)
	    {	
		char ciphertexts_filename[FILENAME_BUFFER_SIZE];
		sprintf(ciphertexts_filename, CIPHERTEXTS_FILE_TMPL.c_str(), l);
	
		std::ifstream ciphtext_stream(ciphertexts_filename, std::fstream::in);

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
		char filename[FILENAME_BUFFER_SIZE];

		sprintf(filename, PERMUTATION_COMMIMENTS_FILE_TMPL.c_str(), l);	
		mu = Node(filename);

		sprintf(filename, POS_COMMITMENT_FILE_TMPL.c_str(), l);	
		tau_pos = Node(filename);

		sprintf(filename, POS_REPLY_FILE_TMPL.c_str(), l);	
		sigma_pos = Node(filename);
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
