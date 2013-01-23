#include "IntLeaf.h"

#define ARRAYORDER 1 /* -1 for least significant byte first, 1 for most significant byte first */
#define ENDIAN 0
#define NAILS 0

IntLeaf::IntLeaf(void)
{
}

IntLeaf::IntLeaf(std::vector<char> bytevec)
{
    bool negative = false;

    /* Check if negative - if signed bit is 1 */
    if(ARRAYORDER == 1)
	negative = bytevec[0] & 0x80;
    else
	negative = bytevec[bytevec.size()-1] & 0x80;

    if(negative) 
    {
	/* Change to corresponding positive number using two's complement */
	for(unsigned int i=0; i < bytevec.size(); i++)
	{
	    bytevec[i] ^= 0xFF;
	}

	if(ARRAYORDER == 1)
	    bytevec[bytevec.size() - 1]++;
	else
	    bytevec[0]++;
    }

    mpz_import(data.get_mpz_t(), bytevec.size(), ARRAYORDER, 
	       sizeof(bytevec[0]), ENDIAN, NAILS, bytevec.data());

    if(negative)
	mpz_neg(data.get_mpz_t(), data.get_mpz_t());
}


IntLeaf::~IntLeaf(void)
{
}

int32_t IntLeaf::getLength(void) const
{
    return mpz_sizeinbase(data.get_mpz_t(), 256);
}

std::vector<char> IntLeaf::toVector(void) const 
{
    unsigned int size = mpz_sizeinbase(data.get_mpz_t(), 256);
    std::vector<char> bytevec(size);

    mpz_export(bytevec.data(), NULL, ARRAYORDER, sizeof(bytevec[0]), ENDIAN, NAILS, data.get_mpz_t());

    /* Check if negative */
    bool negative = (mpz_sgn(data.get_mpz_t()) == -1);

    if(negative)
    {
	/* Change to corresponding negative number using two's complement */
	for(unsigned int i=0; i < bytevec.size(); i++)
	{
	    bytevec[i] ^= 0xFF;
	}

	if(ARRAYORDER == 1)
	    bytevec[bytevec.size() - 1]++;
	else
	    bytevec[0]++;
    }

    return bytevec;
}


IntLeaf & IntLeaf::addTo(const IntLeaf & leaf)
{
    data += leaf.data;

    return *this;
}


IntLeaf IntLeaf::add(const IntLeaf & leaf) const
{
    return IntLeaf(*this) += leaf;
}


IntLeaf & IntLeaf::operator+=(const IntLeaf & leaf)
{
    return addTo(leaf);
}


IntLeaf IntLeaf::operator+(const IntLeaf & leaf) const
{
    return add(leaf);
}


IntLeaf & IntLeaf::multTo(const IntLeaf & leaf)
{
    data *= leaf.data;

    return *this;
}


IntLeaf IntLeaf::mult(const IntLeaf & leaf) const
{
    return IntLeaf(*this) += leaf;
}


IntLeaf & IntLeaf::operator*=(const IntLeaf & leaf)
{
    return multTo(leaf);
}


IntLeaf IntLeaf::operator*(const IntLeaf & leaf) const
{
    return mult(leaf);
}



std::string IntLeaf::toString(void) const
{
    return data.get_str();
}

