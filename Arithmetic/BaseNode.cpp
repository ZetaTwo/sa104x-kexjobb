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
	return type;
};

BaseNode *BaseNode::copy(const BaseNode *node) {
	BaseNode *element;
	switch(node->getType()) {
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

	return element;
}

void BaseNode::ReadNodeHeader(std::istream &file, char &type, uint32_t &length) {
	char buffer[4];
	
	file.read(buffer, 1);
	type = buffer[0];

	/* make int out of byte array */
	file.read(buffer, 4);
	length = buffer[0];
	length <<= sizeof(char);
	length |= buffer[1];
	length <<= sizeof(char);
	length |= buffer[2];
	length <<= sizeof(char);
	length |= buffer[3];
}

bytevector BaseNode::concatData(const BaseNode * const other) const {
	bytevector result;
	bytevector thisData = this->serialize();
	bytevector otherData = other->serialize();

	result.insert(result.end(), thisData.begin(), thisData.end());
	result.insert(result.end(), otherData.begin(), otherData.end());

	return result;
}

bytevector BaseNode::serialize() const {
	bytevector result;
	if(getType() == BaseNode::NODE) {
		result.push_back(0);
	} else {
		result.push_back(1);
	}

	IntLeaf length(getLength(), 4);
	bytevector lengthData = length.toVector();
	result.insert(result.end(), lengthData.begin(), lengthData.end());

	bytevector data = toVector();
	result.insert(result.end(), data.begin(), data.end());

	return result;
}
