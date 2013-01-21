#include "Node.h"

#include <stdexcept>

Node::Node(int32_t length) : BaseNode(BaseNode::NODE, length), children(length, NULL)
{
}

Node::~Node(void)
{
}

BaseNode* const &Node::operator[](int32_t index) const {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return children[index];
}

BaseNode* &Node::operator[](int32_t index) {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return children[index];
}
