#include "BaseNode.h"

BaseNode::BaseNode(BaseNode::NodeType type) : type(type)
{
}

BaseNode::~BaseNode(void)
{
}

BaseNode::NodeType BaseNode::getType(void) const {
	return type;
};
