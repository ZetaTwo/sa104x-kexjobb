#include <vector>
#include <fstream>

#include "KeyVerifier.h"
#include "Node.h"
#include "IntLeaf.h"

Node *verifyKeys(int nr_servers, Node &G)
{

    // Step 1
    Node pk = Node(FULL_PUBLIC_KEY_FILE_NAME);
    
    if(!isPublicKey(pk))
    {
        // Did not read a key from file, reject proof
	// throw exception?
    }

    // Step 2
    Node pub_keys = Node();
    IntLeaf pub_key;
    
    for(int i=0; i<nr_servers; i++) 
    {
	const std::string partial_public_key_file_name = 
	    PARTIAL_PUBLIC_KEY_FILE_PREFIX + std::to_string(i) + std::string(".bt");
	
	std::ifstream fstr(partial_public_key_file_name, std::fstream::in);

	if(fstr)
	{
	    pub_key = IntLeaf(fstr);

	    if(!isPartialPublicKey(pub_key))
	    {
		// Did not read a key from file, reject proof
		// throw exception?
	    }
    
	    pub_keys.addChild(pub_key);
	}

    }

    IntLeaf &g = static_cast<IntLeaf &>(pk.getChild(0));
    IntLeaf &y = static_cast<IntLeaf &>(pk.getChild(1));
    IntLeaf &p = static_cast<IntLeaf &>(G.getChild(0));

    if(pub_keys.prod() != y)
    {
	// Public keys do not match, reject proof
	// throw exception?
    }
    

    // Step 3
    Node sec_keys = Node();
    IntLeaf sec_key;
    for(int i=0; i<nr_servers; i++)
    {
	const std::string partial_secret_key_file_name = 
	    PARTIAL_SECRET_KEY_FILE_PREFIX + std::to_string(i) + std::string(".bt");
	
	std::ifstream fstr(partial_secret_key_file_name, std::fstream::in);
	if(fstr)
	{   
	    sec_key = IntLeaf(fstr);
	    
	    if(!isPartialSecretKey(sec_key))
	    {
		// Did not read a key from file, reject proof
		// throw exception?
	    }

	    if(sec_key != g.expMod(sec_key, p))
	    {
		// secret key does not match public key, reject proof
		// throw exception?
	    }
	    
	}
	else
	{
	    /* Set nonsense value? */
	    sec_key = IntLeaf(-1);
	}

	sec_keys.addChild(sec_key);
    }


    // Step 4
    Node *ret = new Node();

    ret->addChild(pk);
    ret->addChild(pub_keys);
    ret->addChild(sec_keys);

    return ret;
}


bool isPublicKey(Node &node) 
{
    return true;
}

bool isPartialPublicKey(IntLeaf &leaf)
{
    return true;
}

bool isPartialSecretKey(IntLeaf &leaf)
{
    return true;
}
