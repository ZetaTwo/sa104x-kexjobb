#include "Leaf.h"

#include <stdexcept>

Leaf::Leaf(int32_t length) : BaseNode(NodeType::LEAF, length), data(length, 0)
{
}


Leaf::~Leaf(void)
{
}

const std::vector<char> Leaf::getData(void) const {
	return data;
}

char &Leaf::operator[](int32_t index) {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return data[index];
}

const char &Leaf::operator[](int32_t index) const {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return data[index];
}