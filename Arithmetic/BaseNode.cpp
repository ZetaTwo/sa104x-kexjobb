#include "BaseNode.h"

BaseNode::BaseNode(void): type(BaseNode::LEAF)
{
}

BaseNode::BaseNode(BaseNode::NodeType type) : type(type)
{
}

BaseNode::~BaseNode(void)
{
}

char BaseNode::getType(void) const {
	return type;
};
