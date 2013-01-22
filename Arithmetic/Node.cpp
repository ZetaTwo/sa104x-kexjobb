#include "Node.h"

#include <stdexcept>

Node::Node() : BaseNode(BaseNode::NODE)
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

int32_t Node::getLength(void) const {
	return children.size();
};