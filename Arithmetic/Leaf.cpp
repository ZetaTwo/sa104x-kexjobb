#include "Leaf.h"

#include <stdexcept>

Leaf::Leaf(int32_t length) : BaseNode(NodeType::LEAF, length)
{
	data = new char[getLength()];
}


Leaf::~Leaf(void)
{
	delete[] data;
}

char *Leaf::getData(void) const {
	return data;
}

char &Leaf::operator[](int32_t index) const {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return data[index];
}