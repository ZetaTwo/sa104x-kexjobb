#include <vector>
#include <fstream>

#include "KeyVerifier.h"
#include "Node.h"
#include "IntLeaf.h"
#include "FileNames.h"


bool keyVerifier(int lambda, proofStruct &pfStr)
{
    Node pk;
    // Step 1 - Read public key from file and reject if not successful
    try {
	pk = Node(FULL_PUBLIC_KEY_FILE);
    }
    catch(...)
    {
	// Something wrong with file/nonexisting file
	return false;
    }

    // Check if public key is OK
    if(!isPublicKey(pfStr.Gq, pk))
    {
        // Did not read a key from file, reject proof
        return false;
    }

    // Step 2 - Read partial public keys and check consistency with public key
    Node pub_keys;
    IntLeaf pub_key;
    
    for(int i=1; i <= lambda; i++) 
    {
	// Read correct file for partial public key nr i
	char ppk_filename[FILENAME_BUFFER_SIZE];
	sprintf(ppk_filename, PARTIAL_PUBLIC_KEY_FILE_TMPL.c_str(), i);

	try
	{
	    pub_key = IntLeaf(ppk_filename);
	}
	catch(...)
	{
	    // Not possible to read file
	    return false;
	}

	// Check to see if partial public key is OK
	if(!isPartialPublicKey(pfStr.Gq, pub_key))
	{
	    // Did not read a key from file, reject proof
	    return false;
	}
	
	// Save partial public key in partial public key array
	pub_keys.addChild(pub_key);
    }

    // Save public key pk = (g,y) and max size of ints p for convenience
    const IntLeaf &g = pk.getIntLeafChild(0);
    const IntLeaf &y = pk.getIntLeafChild(1);
    const IntLeaf &p = pfStr.Gq.getIntLeafChild(0);

    // multiply ppk:s and check that the product is consistent with pk
    if(pub_keys.prod() != y)
    {
	// Public keys do not match, reject proof
	return false;
    }
    

    // Step 3 - read partial secret keys 
    
    Node sec_keys;
    IntLeaf sec_key;

    for(int i=1; i<=lambda; i++)
    {
	// Create correct filename
	char psk_filename[FILENAME_BUFFER_SIZE];
	sprintf(psk_filename, PARTIAL_SECRET_KEY_FILE_TMPL.c_str(), i);
	
	std::ifstream fstr(psk_filename, std::fstream::in);
	
	// If file exists
	if(fstr)
	{   
	    sec_key = IntLeaf(fstr);
	    
	    // Check to see if sec_key is really a secret key
	    if(!isPartialSecretKey(pfStr.Gq, sec_key))
	    {
		// Did not read a valid key from file, reject proof
		return false;
	    }

	    // Check consistency with ppk:s, (children indices starts with 0)
	    if(pub_keys.getIntLeafChild(i-1) != g.expMod(sec_key, p))
	    {
		// Secret key does not match public key, reject proof
	        return false;
	    }
	    
	}

	// If file does not exist
	else
	{
	    // Set invalid value to mark this
	    sec_key = BOTTOM;
	}

	// Add psk to psk array
	sec_keys.addChild(sec_key);
    }


    // Step 4
    
    // Save keys to proofStruct instead of returning array
    pfStr.pk = pk;
    pfStr.y = pub_keys;
    pfStr.x = sec_keys;

    return true;
}


bool isPublicKey(const Node &G, const Node &pk) 
{
    // A public key pk = (g,y) where g and y are elements of Gq
    if(isElemOfGq(G, pk.getIntLeafChild(0)) &&
       isElemOfGq(G, pk.getIntLeafChild(1)))
    {
	return true;
    }

    return false;
}

bool isPartialPublicKey(const Node &G, const IntLeaf &ppk)
{
    // A partial public key ppk is an element of Gq
    return isElemOfGq(G, ppk);
}

bool isPartialSecretKey(const Node &G, const IntLeaf &psk)
{
    // A partial secret key pskk is an element of Zq, where q is the same as in Gq
    return isElemOfZn(G.getIntLeafChild(1), psk);
}
