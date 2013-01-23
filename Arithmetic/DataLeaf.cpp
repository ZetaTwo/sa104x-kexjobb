#include "DataLeaf.h"

#include <stdexcept>
#include <gmp.h>

#define ARRAYORDER -1 /* -1 for least significant first, 1 for most significant first */

DataLeaf::DataLeaf(void) : BaseLeaf(BaseNode::LEAF)
{
}

DataLeaf::DataLeaf(int32_t size) : BaseLeaf(BaseNode::LEAF)
{
    data.resize(size);
}

DataLeaf::~DataLeaf(void)
{
}

std::vector<char> &DataLeaf::getData(void) {
	return data;
}

const std::vector<char> &DataLeaf::getData(void) const {
        return data;
}

int32_t DataLeaf::getLength(void) const {
	return data.size();
};


DataLeaf &DataLeaf::operator=(const DataLeaf &leaf)
{
        if(this == &leaf)
    	    return *this;

        data = leaf.toVector();

        return *this;
}

std::vector<char> DataLeaf::toVector(void) const {
	return std::vector<char>();
}


