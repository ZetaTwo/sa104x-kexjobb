#include "Utilities.h"

bool isElemOf(const Node &group, const IntLeaf &elem)
{
    const IntLeaf &p = static_cast<const IntLeaf &>(group.getChild(0));
    const IntLeaf &q = static_cast<const IntLeaf &>(group.getChild(1));

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
    return true;
}
