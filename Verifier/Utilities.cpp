#include "Utilities.h"

#include <vector>

bool isElemOf(const Node &group, const IntLeaf &elem)
{
    const IntLeaf &p = group.getIntLeafChild(0);
    const IntLeaf &q = group.getIntLeafChild(1);

    if(!(elem < p) || !(elem > IntLeaf(0)))
	return false;

    if(elem.expMod(q, p) != IntLeaf(1))
	return false;

    return true;
}

bool isElemOf(const IntLeaf &Zn, const IntLeaf &elem)
{
    if(!(elem < Zn) || elem < IntLeaf(0))
	return false;

    return true;
}



bool isPedersenCommitment(const Node &group, const IntLeaf &elem)
{
    return isElemOf(group, elem);
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
