#include "Node.h"

#include <stdexcept>

Node::Node(int32_t length) : BaseNode(NodeType::NODE, length)
{
	children = new BaseNode*[getLength()];
}

Node::~Node(void)
{
	delete[] children;
}

BaseNode *&Node::operator[](int32_t index) const {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return children[index];
}