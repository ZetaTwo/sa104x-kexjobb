#include "Utilities.h"

#include <vector>

bool isElemOfGq(const Node &group, const IntLeaf &elem)
{
    const IntLeaf &p = group.getIntLeafChild(0);
    const IntLeaf &q = group.getIntLeafChild(1);

    if(!(elem < p) || (elem < IntLeaf(1)))
	return false;

    // A group element raised to the group order equals identity
    if(elem.expMod(q, p) != IntLeaf(1))
	return false;

    return true;
}

bool isElemOfZn(const IntLeaf &n, const IntLeaf &elem)
{
    if(!(elem < n) || elem < IntLeaf(0))
	return false;

    return true;
}


bool isElemOfMw(const proofStruct &pfStr, const Node &plaintext)
{
    // The plaintext group Mw is Gq x ... Gq, width times

    try {
	for(unsigned int i=0; i<pfStr.width; ++i)
	{
	    IntLeaf g = plaintext.getIntLeafChild(i);
	    if(!isElemOfGq(pfStr.Gq, g))
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

bool isElemOfCw(const proofStruct &pfStr, const Node &ciphertext)
{
    // The Ciphertext group Cw = Mw x Mw
    // hence the elements of Cw must be a pair of Nodes
    // where both Nodes are elements of Cw.

    try {
	Node u = ciphertext.getNodeChild(0);
	Node v = ciphertext.getNodeChild(1);

	if(!isElemOfMw(pfStr, u) || !isElemOfMw(pfStr, v))
	{
	    return false;
	}
    }
    catch(...)
    {
	return false;
    }

    return true;
}

bool isElemOfRw(const proofStruct &pfStr, const Node &random)
{
    for(unsigned int i=0; i<pfStr.width; ++i)
    {
	if(!isElemOfZn(pfStr.Gq.getIntLeafChild(1), random.getIntLeafChild(i)))
	{
	    return false;
	}
    }

    return true;
}


bool isPedersenCommitment(const Node &group, const IntLeaf &elem)
{
    return isElemOfGq(group, elem);
}


void getGroupFromString(proofStruct &pfStr, std::string str)
{
    bytevector byte_vec;

    unsigned int i=0;

    while(str[i] != ':' && str[i+1] != ':')
    {
	++i;
    }

    char *buffer = new char[3];
    buffer[2] = 0;

    for(; i<str.size(); ++i)
    {	
	for(int j=0; j<2; ++j)
	{
	    if(str[i] == ' ') {
		++i;
	    }
	    
	    buffer[j] = str[i];
	}
    
	byte_vec.push_back(strtoul(buffer, NULL, 16));
    }
    
    delete buffer;

    Node group_info = Node(byte_vec);

    /* TODO: Here is a good place to check if the first child of group_info is a string which says verificatum.arithm.ModPGroup */

    pfStr.Gq = group_info.getNodeChild(1);
}
