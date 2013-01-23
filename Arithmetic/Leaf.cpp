#include "Leaf.h"

#include <stdexcept>
#include <gmp.h>

#define ARRAYORDER -1 /* -1 for least significant first, 1 for most significant first */

Leaf::Leaf(void) : BaseNode(BaseNode::LEAF)
{
}

Leaf::Leaf(int32_t size) : BaseNode(BaseNode::LEAF)
{
    data.resize(size);
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
        /* Make big int from this->data */
        mpz_t a;
        mpz_init(a);
        /* Read in char array into big int a */
        mpz_import(a, data.size(), ARRAYORDER, sizeof(data[0]), 0, 0, data.data());

        /* Make big int from leaf.data */
        mpz_t b;
        mpz_init(b);
        /* Read in char array into big int b */
        mpz_import(b, leaf.data.size(), ARRAYORDER, sizeof(leaf.data[0]), 0, 0, leaf.data.data());

        /* Perform addition and save result in a */
        mpz_add(a, a, b);

        /* Export result to char vector (this->data) */
        data.resize(mpz_sizeinbase(a, 256));
        mpz_export(data.data(), NULL, -1, sizeof(data[0]), 1, 0, a);

        return *this;
}

Leaf Leaf::operator+(const Leaf & leaf) const 
{
        return Leaf(*this) += leaf;
}

Leaf & Leaf::operator*=(const Leaf & leaf) 
{
        /* Make big int from this->data */
        mpz_t a;
        mpz_init(a);
        /* Read in char array into big int a */
        mpz_import(a, data.size(), ARRAYORDER, sizeof(data[0]), 0, 0, data.data());

        /* Make big int from leaf.data */
        mpz_t b;
        mpz_init(b);
        /* Read in char array into big int a */
        mpz_import(b, leaf.data.size(), ARRAYORDER, sizeof(leaf.data[0]), 0, 0, leaf.data.data());

        /* Perform multiplication and save result in a */
        mpz_mul(a, a, b);

        /* Save result in char vector */
        data.resize(mpz_sizeinbase(a, 256));
        mpz_export(data.data(), NULL, -1, sizeof(data[0]), 1, 0, a);

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
