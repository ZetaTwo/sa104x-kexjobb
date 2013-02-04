#include <fstream>
#include <string>

#include "Node.h"
#include "IntLeaf.h"

bool verifyShuffling(rho, int lambda, N, nE, nR, nV, PRG, Node &Gq, Rw, Cw, Node &pk, Node &L0, Node &Llambda, posc, ccpos)
{
    std::ifstream fstr(MAXCIPH_FILE_NAME, std::fstream::in);
    
    // maxciph does not exist
    if(!fstr)
    {
	Node L_array = Node();	
	L_array.addChild(L0);

	for(int l=1; l<=lambda; l++)
	{
	    // Step 1
	    if(l < lambda)
	    {
		const std::string cipher_text_file_name = 
		    CIPHER_TEXTS_FILE_NAME + std::to_string(i) + std::string(".bt");
		
		std::ifstream ciphtext_stream(cipher_text_file_name, std::fstream::in);
		
		if(!ciphtext_stream)
		    return false;

		Node L = Node(ciphtext_stream);

		if(!isListOfCipherTexts(L))
		    return false;

		L_array.addChild(L);
	    }
	    else
	    {
		L_array.addChild(Llambda);
	    }

	    // Step 2
	    // Verify proof of shuffle
	    // Execute Algorithm 19 with specified input
	    if(!Algorithm19(/* arg list */) && L.getChild(i) != L.getChild(i-1))
		return false;

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



