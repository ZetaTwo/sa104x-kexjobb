#include "BaseNode.h"
#include "Node.h"
#include "IntLeaf.h"
#include "DataLeaf.h"

BaseNode::BaseNode(BaseNode::NodeType type) : type(type)
{
}

BaseNode::~BaseNode(void)
{
}

BaseNode::NodeType BaseNode::getType(void) const {
	return type; //Simply return the type
};

BaseNode *BaseNode::copy(const BaseNode *node) {
	//Create the result pointer
	BaseNode *element;

	//Cast node to the correct type and call the corresponing copy constructor
	switch(node->getType()) { //Which kind of node are we working with?
	case BaseNode::INT_LEAF:
		element = new IntLeaf(*static_cast<const IntLeaf *>(node));
		break;
	case BaseNode::NODE:
		element = new Node(*static_cast<const Node *>(node));
		break;
	case BaseNode::DATA_LEAF:
		element = new DataLeaf(*static_cast<const DataLeaf *>(node));
		break;
	default:
		break;
	}

	//Return the result
	return element;
}

void BaseNode::ReadNodeHeader(std::istream &file, char &type, uint32_t &length) {
	//Prepare a big enough header
	char buffer[4];
	
	//Read the first byte which indicates which type of node it is.
	file.read(buffer, 1);
	type = buffer[0];

	//Read the following 4 bytes and convert them into one integer
	file.read(buffer, 4);
	length = ((unsigned char)buffer[0] << 3*sizeof(char)) + ((unsigned char)buffer[1] << 2*sizeof(char)) +
		((unsigned char)buffer[2] << 1*sizeof(char)) + ((unsigned char)buffer[3] << 0*sizeof(char));
}

bytevector BaseNode::concatData(const BaseNode * const other) const {
	//Prepare the result
	bytevector result;

	//Serialize the two halves.
	bytevector thisData = this->serialize();
	bytevector otherData = other->serialize();

	//Concat the data.
	result.insert(result.end(), thisData.begin(), thisData.end());
	result.insert(result.end(), otherData.begin(), otherData.end());

	//Return the result.
	return result;
}

bytevector BaseNode::serialize() const {
	//Prepare the result.
	bytevector result;

	//Insert the correct type
	if(getType() == BaseNode::NODE) {
		result.push_back(0);
	} else {
		result.push_back(1);
	}

	//Insert the 4 bytes indicating the length.
	IntLeaf length(getLength(), 4);
	bytevector lengthData = length.toVector();
	result.insert(result.end(), lengthData.begin(), lengthData.end());

	//Insert the actual data.
	bytevector data = toVector();
	result.insert(result.end(), data.begin(), data.end());

	//Return the result.
	return result;
}
