#include "Leaf.h"

#include <stdexcept>

Leaf::Leaf(void) : BaseNode(BaseNode::LEAF)
{
}

Leaf::~Leaf(void)
{
}

std::vector<char> &Leaf::getData(void) {
	return data;
}

const std::vector<char> &Leaf::getData(void) const {
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


Leaf &Leaf::operator=(const Leaf &leaf)
{
        if(this == &leaf)
    	    return *this;

        data = leaf.getData();

        return *this;
}

Leaf & Leaf::operator+=(const Leaf & leaf) 
{
        // Replace with real code, with big integers
        data[0]+=leaf[0];

        return *this;
}

Leaf Leaf::operator+(const Leaf & leaf) const 
{
        return Leaf(*this) += leaf;
}

Leaf & Leaf::operator*=(const Leaf & leaf) 
{
        // Replace with real code, with big integers
        data[0]*=leaf[0];

        return *this;
}

Leaf Leaf::operator*(const Leaf & leaf) const 
{
        return Leaf(*this) *= leaf;
}

bool Leaf::operator==(const Leaf &leaf) const
{
        if(data == leaf.getData())
	    return true;

        return false;
}
