#include "DataLeaf.h"

#include <stdexcept>

DataLeaf::DataLeaf(void) : BaseLeaf(BaseNode::DATA_LEAF)
{
}

DataLeaf::DataLeaf(int32_t size) : BaseLeaf(BaseNode::DATA_LEAF), data(size)
{
}

DataLeaf::DataLeaf(std::istream &file) : BaseLeaf(BaseNode::DATA_LEAF)
{
	//Retrieve type and length
    char type;
    uint32_t length;
    ReadNodeHeader(file, type, length);

    if(type != 0x01) {
		//TODO
		// Trying to build a dataleaf from a node, throw exception?
		throw 1;
    }
   
	//Read and store the data;
    for (uint32_t i = 0; i < length; i++)
    {
		char buffer;
		file.read(&buffer, 1);
		data.push_back(buffer);
    }
}


DataLeaf::DataLeaf(std::string str) : BaseLeaf(BaseNode::DATA_LEAF)
{
	//Copy the string into data
    data = bytevector(str.begin(), str.end());
}

DataLeaf::~DataLeaf(void)
{
}

bytevector &DataLeaf::getData(void) {
    return data; //Simply return the data vector.
}

const bytevector &DataLeaf::getData(void) const {
    return data; //Simply return the data vector.
}

int32_t DataLeaf::getLength(void) const {
    return data.size(); //Simply return the data size.
};


DataLeaf &DataLeaf::operator=(const DataLeaf &leaf)
{
	//Prevent self assignment
    if(this != &leaf)  {
		//Assign the data of leaf to data.
	    data = leaf.toVector();
	}

	//Return a reference to this object.
    return *this;
}

bytevector DataLeaf::toVector(void) const {
    return data; //Simply return the data.
}
