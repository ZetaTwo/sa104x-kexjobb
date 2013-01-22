#include "Leaf.h"

#include <stdexcept>

Leaf::Leaf(void) : BaseNode(BaseNode::LEAF)
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

int32_t Leaf::getLength(void) const {
	return data.size();
};