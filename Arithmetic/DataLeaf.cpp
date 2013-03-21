#include "DataLeaf.h"

#include <stdexcept>
//#include <gmp.h>

#define ARRAYORDER -1 /* -1 for least significant first, 1 for most significant first */

DataLeaf::DataLeaf(void) : BaseLeaf(BaseNode::DATA_LEAF)
{
}

DataLeaf::DataLeaf(int32_t size) : BaseLeaf(BaseNode::DATA_LEAF), data(size)
{
}

DataLeaf::DataLeaf(std::istream &file) : BaseLeaf(BaseNode::DATA_LEAF)
{
    char type;
    uint32_t length;

    ReadNodeHeader(file, type, length);

    if(type != 0x01) {
	//TODO
	/* Trying to build a dataleaf from a node, throw exception? */
    }
   
    for (uint32_t i = 0; i < length; i++)
    {
	char buffer;
	file.read(&buffer, 1);
	data.push_back(buffer);
    }
}


DataLeaf::DataLeaf(std::string str) : BaseLeaf(BaseNode::DATA_LEAF)
{
    data = bytevector(str.begin(), str.end());
}

DataLeaf::~DataLeaf(void)
{
}

bytevector &DataLeaf::getData(void) {
    return data;
}

const bytevector &DataLeaf::getData(void) const {
    return data;
}

int32_t DataLeaf::getLength(void) const {
    return data.size();
};


DataLeaf &DataLeaf::operator=(const DataLeaf &leaf)
{
    if(this == &leaf) {
	return *this;
    }

    data = leaf.toVector();

    return *this;
}

bytevector DataLeaf::toVector(void) const {
    return data;
}


