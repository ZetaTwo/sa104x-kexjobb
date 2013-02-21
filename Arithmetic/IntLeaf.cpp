#include "IntLeaf.h"

IntLeaf::IntLeaf(const IntLeaf &leaf) : BaseLeaf(BaseNode::INT_LEAF), data(leaf.data), length(0)
{
}

IntLeaf::IntLeaf(void) : data(0) , BaseLeaf(BaseNode::INT_LEAF), length(0)
{
}

IntLeaf::IntLeaf(long int input) : BaseLeaf(BaseNode::INT_LEAF), data(input), length(0)
{
}

IntLeaf::IntLeaf(long int input, long int length) : BaseLeaf(BaseNode::INT_LEAF), data(input), length(length)
{
}

IntLeaf::IntLeaf(const mpz_class &bigint) : BaseLeaf(BaseNode::INT_LEAF), data(bigint)
{
}

IntLeaf::IntLeaf(std::string input) : BaseLeaf(BaseNode::INT_LEAF), data(input), length(0)
{
}

IntLeaf::IntLeaf(std::vector<unsigned char> bytevec) : BaseLeaf(BaseNode::INT_LEAF)
{
    bool negative = false;

    length = bytevec.size();

    /* Check if negative - if signed bit is 1 */
    if(ARRAYORDER == 1) {
		negative = bytevec[0] & 0x80;
	} else {
		negative = bytevec[bytevec.size()-1] & 0x80;
	}

    if(negative) 
    {
		/* Change to corresponding positive number using two's complement */
		for(unsigned int i=0; i < bytevec.size(); i++)
		{
			bytevec[i] ^= 0xFF;
		}

		if(ARRAYORDER == 1) {
			bytevec[bytevec.size() - 1]++;
		} else {
			bytevec[0]++;
		}
    }

    mpz_import(data.get_mpz_t(), bytevec.size(), ARRAYORDER, 
	       sizeof(bytevec[0]), ENDIAN, NAILS, bytevec.data());

    if(negative)
	mpz_neg(data.get_mpz_t(), data.get_mpz_t());
}

IntLeaf::~IntLeaf(void)
{
}

BaseNode *IntLeaf::constructPartFromFile(std::istream &file, uint32_t length) {
	
	std::vector<unsigned char> data;
	for (uint32_t i = 0; i < length; i++)
	{
		char buffer[1];
		file.read(buffer, 1);
		data.push_back(buffer[0]);
	}

	IntLeaf *result = new IntLeaf(data);

	return result;
}


IntLeaf &IntLeaf::operator=(const IntLeaf &leaf)
{
    this->data = leaf.data;

    return *this;
}


IntLeaf &IntLeaf::operator=(long int input)
{
    this->data = static_cast<long int>(input);

    return *this;
}


IntLeaf &IntLeaf::operator=(std::string input)
{
    data = input;

    return *this;
}


IntLeaf & IntLeaf::modTo(const IntLeaf & leaf)
{
    this->data = this->data % leaf.data;

    return *this;
}


IntLeaf IntLeaf::mod(const IntLeaf & leaf) const
{
    return IntLeaf(*this).modTo(leaf);
}


IntLeaf & IntLeaf::addTo(const IntLeaf & leaf)
{
    this->data += leaf.data;

    return *this;
}


IntLeaf IntLeaf::add(const IntLeaf & leaf) const
{
    return IntLeaf(*this) += leaf;
}


IntLeaf & IntLeaf::addToMod(const IntLeaf & leaf, const IntLeaf & mod)
{
    (*this) += leaf;
    this->data %= mod.data;

    return *this;
}

IntLeaf IntLeaf::addMod(const IntLeaf & leaf, const IntLeaf & mod) const
{
    IntLeaf res = (*this);
    res.addToMod(leaf, mod);
    
    return res;
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
    this->data *= leaf.data;

    return *this;
}


IntLeaf IntLeaf::mult(const IntLeaf & leaf) const
{
    return IntLeaf(*this) *= leaf;
}

IntLeaf &IntLeaf::multToMod(const IntLeaf &leaf, const IntLeaf &mod)
{
    (*this) *= leaf;
    this->data %= mod.data;

    return (*this);
}


IntLeaf IntLeaf::multMod(const IntLeaf &leaf, const IntLeaf &mod) const
{
    IntLeaf res = *this;
    res.multToMod(leaf, mod);

    return res;
}


IntLeaf & IntLeaf::operator*=(const IntLeaf & leaf)
{
    return multTo(leaf);
}


IntLeaf IntLeaf::operator*(const IntLeaf & leaf) const
{
    return mult(leaf);
}


IntLeaf &IntLeaf::expTo(unsigned long exponent)
{
    mpz_pow_ui(this->data.get_mpz_t(), this->data.get_mpz_t(), exponent);

    return (*this);
}


IntLeaf IntLeaf::exp(unsigned long exponent) const
{
    IntLeaf res = *this;
    res.expTo(exponent);

    return res;
}

IntLeaf &IntLeaf::expToMod(const IntLeaf & leaf, const IntLeaf & mod)
{
    mpz_powm(this->data.get_mpz_t(), this->data.get_mpz_t(), leaf.data.get_mpz_t(), mod.data.get_mpz_t());

    return *this;
}


IntLeaf IntLeaf::expMod(const IntLeaf & leaf, const IntLeaf & mod) const
{
    IntLeaf res = *this;
    res.expToMod(leaf, mod);

    return res;
}


bool IntLeaf::operator==(const IntLeaf &leaf) const
{
    return (this->data == leaf.data);
}


bool IntLeaf::operator!=(const IntLeaf &leaf) const
{
    return !(*this == leaf);
}

bool IntLeaf::operator<(const IntLeaf &leaf) const
{
    return this->data < leaf.data;
}

bool IntLeaf::operator>(const IntLeaf &leaf) const
{
    return !(*this < leaf) || (*this == leaf);
}

IntLeaf IntLeaf::operator-(void) const {
	return (*this) * -1;
}

IntLeaf IntLeaf::inverse(const IntLeaf &mod) const
{
    mpz_class res;

    if(mpz_invert(res.get_mpz_t(), data.get_mpz_t(), mod.getBigInt().get_mpz_t()) != 0)
    {
        // throw exception?
    }

    return IntLeaf(res);
} 


mpz_class IntLeaf::getBigInt(void) const
{
    return data;
}


std::vector<unsigned char> IntLeaf::toVector(void) const 
{
    /* number of bytes needed for bigint */
    unsigned int size = mpz_sizeinbase(data.get_mpz_t(), 256);
    
    std::vector<unsigned char> bytevec(getLength(), 0);

    /* if getLength() != size the first (getLength() - size) bytes will be zero as they should */
    mpz_export(bytevec.data() + (getLength() - size), NULL, ARRAYORDER, sizeof(bytevec[0]), ENDIAN, NAILS, data.get_mpz_t());

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


int32_t IntLeaf::getLength(void) const
{
    /* This happens if IntLeaf was not constructed from file or byte vector */
    if(length == 0) {
	return mpz_sizeinbase(data.get_mpz_t(), 256);
    } else {
	return length;
    }
}


std::string IntLeaf::toString(void) const
{
    return data.get_str();
}



