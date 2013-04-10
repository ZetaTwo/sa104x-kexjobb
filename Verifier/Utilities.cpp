#include "Utilities.h"

#include <vector>
#include <algorithm>

bool isElemOfGq(const Node &group, const IntLeaf &elem)
{
    // For convenience
    const IntLeaf &p = group.getIntLeafChild(0);
    const IntLeaf &q = group.getIntLeafChild(1);

    // Make sure elem is in allowed range for elements in Gq
    if(!(elem < p) || (elem < IntLeaf(1)))
	return false;

    // A group element raised to the group order equals identity
    if(elem.expMod(q, p) != IntLeaf(1))
	return false;

    return true;
}

bool isElemOfZn(const IntLeaf &n, const IntLeaf &elem)
{
    // Need only test to make sure elem is within allowed range
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
	// Return false if there are not enough children for example
	return false;
    }

    return true;
}

bool isElemOfCw(const proofStruct &pfStr, const Node &uv)
{
    // The Ciphertext group Cw = Mw x Mw
    // hence the elements of Cw must be a pair of Nodes
    // where both Nodes are elements of Mw.

    //ciphertext = (u,v) in Mw x Mw 
    try {
        if(!isElemOfMw(pfStr, uv.getNodeChild(0)) || !isElemOfMw(pfStr, uv.getNodeChild(1)))
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
    // Rw is Z_q x ... x Z_q, width times

    for(unsigned int i=0; i<pfStr.width; ++i)
    {
	// Gq = (p,q,g,..)
	if(!isElemOfZn(pfStr.Gq.getIntLeafChild(1), random.getIntLeafChild(i)))
	{
	    return false;
	}
    }

    return true;
}


bool isPedersenCommitment(const Node &group, const IntLeaf &elem)
{
    // A pedersen commitment is an element in Gq
    return isElemOfGq(group, elem);
}


void getGroupFromString(proofStruct &pfStr, std::string str)
{
	//Prepare data vector
    bytevector byte_vec;

	//Remove prefix and whitespace
	str.erase(str.begin(), str.begin()+str.find("::")+2);
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

	//Parse string as bytes
	char buffer[3];
	unsigned int c;
	buffer[2] = 0;
	for(int pos = 0; pos < str.length(); pos+=2) {
		buffer[0] = str[pos];
		buffer[1] = str[pos+1];
        sscanf(buffer, "%2hhx", &c);

		byte_vec.push_back(c);
    }

	//Convert to Node
    Node group_info = Node(byte_vec);

	//Get the group type data
    IntLeaf groupType = group_info.getIntLeafChild(0);
	bytevector groupTypeData = groupType.toVector();

	//Create expected data vector
	char groupTypeExpected[] = "verificatum.arithm.ModPGroup";
	bytevector groupTypeDataExpected;
	groupTypeDataExpected.insert(groupTypeDataExpected.end(), groupTypeExpected, groupTypeExpected+28);

	//Verify that the group type is correct
	if(groupTypeData != groupTypeDataExpected) {
		//TODO: Fel sorts grupp
		throw 1;
	}

	//Save result in proof struct
    pfStr.Gq = group_info.getNodeChild(1);
}
