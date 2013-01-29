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
