#include <vector>
#include <fstream>

#include "KeyVerifier.h"
#include "Node.h"
#include "IntLeaf.h"
#include "FileNames.h"


bool keyVerifier(int lambda, proofStruct &pfStr)
{
    // Step 1
    Node pk = Node(FULL_PUBLIC_KEY_FILE);
    
    if(!isPublicKey(pfStr.Gq, pk))
    {
        // Did not read a key from file, reject proof
        return false;
    }

    // Step 2
    Node pub_keys = Node();
    IntLeaf pub_key;
    
    for(int i=1; i <= lambda; i++) 
    {
		char istr[21];
		itoa(i, istr, 10);
	const std::string partial_public_key_file_name = 
	    PARTIAL_PUBLIC_KEY_FILE_PREFIX + istr + FILE_SUFFIX;
	
	std::ifstream fstr(partial_public_key_file_name, std::fstream::in);

	if(fstr)
	{
	    pub_key = IntLeaf(fstr);

	    if(!isPartialPublicKey(pfStr.Gq, pub_key))
	    {
		// Did not read a key from file, reject proof
		return false;
	    }
    
	    pub_keys.addChild(pub_key);
	}

    }

    const IntLeaf &g = pk.getIntLeafChild(0);
    const IntLeaf &y = pk.getIntLeafChild(1);
    const IntLeaf &p = pfStr.Gq.getIntLeafChild(0);

    if(pub_keys.prod() != y)
    {
	// Public keys do not match, reject proof
	return false;
    }
    

    // Step 3
    Node sec_keys;
    IntLeaf sec_key;
    for(int i=1; i<=lambda; i++)
    {
	const std::string partial_secret_key_file_name = 
	    PARTIAL_SECRET_KEY_FILE_PREFIX + std::to_string(i) + FILE_SUFFIX;
	
	std::ifstream fstr(partial_secret_key_file_name, std::fstream::in);
	if(fstr)
	{   
	    sec_key = IntLeaf(fstr);
	    
	    if(!isPartialSecretKey(pfStr.Gq, sec_key))
	    {
		// Did not read a valid key from file, reject proof
		return false;
	    }

	    if(pub_keys.getIntLeafChild(i-1) != g.expMod(sec_key, p))
	    {
		// Secret key does not match public key, reject proof
	        return false;
	    }
	    
	}
	else
	{
	    // Set invalid value
	    sec_key = BOTTOM;
	}

	sec_keys.addChild(sec_key);
    }


    // Step 4
    
    pfStr.pk = pk;
    pfStr.y = pub_keys;
    pfStr.x = sec_keys;

    return true;
}


bool isPublicKey(const Node &G, const Node &pk) 
{
    if(isElemOfGq(G, pk.getIntLeafChild(0)) &&
       isElemOfGq(G, pk.getIntLeafChild(1)))
    {
	return true;
    }

    return false;
}

bool isPartialPublicKey(const Node &G, const IntLeaf &ppk)
{
    return isElemOfGq(G, ppk);
}

bool isPartialSecretKey(const Node &G, const IntLeaf &psk)
{
    return isElemOfZn(G.getIntLeafChild(1), psk);
}
