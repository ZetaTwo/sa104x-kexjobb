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
	char* buffer = new char[9];
	file.read(buffer, 2);
	buffer[2] = 0;
	type = strtoul(buffer, NULL, 16);
	file.read(buffer, 8);
	buffer[8] = 0;
	length = strtoul(buffer+1, NULL, 16);
	delete buffer;
}