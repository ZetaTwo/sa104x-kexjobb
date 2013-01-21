#include "BaseNode.h"


BaseNode::BaseNode(BaseNode::NodeType type, int32_t length) : type(type), length(length)
{

}


BaseNode::~BaseNode(void)
{
}

char BaseNode::getType(void) const {
	return type;
};

int32_t BaseNode::getLength(void) const {
	return length;
};