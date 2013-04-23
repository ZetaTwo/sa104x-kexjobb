#include "IntLeaf.h"

IntLeaf::IntLeaf(const IntLeaf &leaf) : BaseLeaf(BaseNode::INT_LEAF), data(leaf.data), length(leaf.length)
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

IntLeaf::IntLeaf(bytevector bytevec) : BaseLeaf(BaseNode::INT_LEAF)
{
	//Assume positive number
    bool negative = false;

	//Get the size of the vector
    length = bytevec.size();

    //Check if negative - if most significant bit is 1
    if(ARRAYORDER == 1) {
		//Check most significant bit of first byte
		negative = bytevec[0] & 0x80;
	} else {
		//Check most significant bit of last byte
		negative = bytevec[bytevec.size()-1] & 0x80;
	}

	//If we have a negative number
    if(negative) 
    {
		//Change to corresponding positive number using two's complement.
		for(unsigned int i=0; i < bytevec.size(); i++)
		{
			//Flip all bits
			bytevec[i] ^= 0xFF;
		}

		//Change the sign byte correctly.
		if(ARRAYORDER == 1) {
			bytevec[bytevec.size() - 1]++;
		} else {
			bytevec[0]++;
		}
    }

	//Create an mpz_class object of the data.
    mpz_import(data.get_mpz_t(), bytevec.size(), ARRAYORDER, 
	       sizeof(bytevec[0]), ENDIAN, NAILS, bytevec.data());

	//If negative, mark the mpz_class so.
    if(negative) {
		mpz_neg(data.get_mpz_t(), data.get_mpz_t());
	}
}

IntLeaf::IntLeaf(std::istream &file) : BaseLeaf(BaseNode::INT_LEAF)
{
	//Get type and length from header
	char type;
	uint32_t length;
	ReadNodeHeader(file, type, length);

	//Construct the node from file data
	data = constructPartFromFile(file, length)->data;
}

IntLeaf::~IntLeaf(void)
{
}

IntLeaf *IntLeaf::constructPartFromFile(std::istream &file, uint32_t length) {
	//Read the data from file
	bytevector data;
	for (uint32_t i = 0; i < length; i++)
	{
		char buffer[1];
		file.read(buffer, 1);
		bool eof = file.eof();
		data.push_back(buffer[0]);
	}

	//Create a new IntLeaf from the data vector
	IntLeaf *result = new IntLeaf(data);

	//Return the result
	return result;
}


IntLeaf &IntLeaf::operator=(const IntLeaf &leaf)
{
	//Overwrite the IntLeaf data
    this->data = leaf.data;

	//Return a reference to this object.
    return *this;
}


IntLeaf &IntLeaf::operator=(long int input)
{
    data = input;

	//Return a reference to this object.
    return *this;
}

IntLeaf &IntLeaf::operator=(std::string input)
{
    data = input;

	//Return a reference to this object.
    return *this;
}

IntLeaf & IntLeaf::modTo(const IntLeaf & leaf)
{
    data %= leaf.data;

	//Return a reference to this object.
    return *this;
}


IntLeaf IntLeaf::mod(const IntLeaf & leaf) const
{
	//Create a copy of this modulo leaf and return the result.
    return IntLeaf(*this).modTo(leaf);
}


IntLeaf & IntLeaf::addTo(const IntLeaf & leaf)
{
	//Add the data of leaf to the data
    data += leaf.data;

	//Return a reference to this object.
    return *this;
}


IntLeaf IntLeaf::add(const IntLeaf & leaf) const
{
	//Create a copy of this object, add leaf and return the result.
    return IntLeaf(*this) += leaf;
}


IntLeaf & IntLeaf::addToMod(const IntLeaf & leaf, const IntLeaf & mod)
{
	//Add leaf to this object
    (*this) += leaf;

	//Modulo mod
    data %= mod.data;

	//Return a reference to this object.
    return *this;
}

IntLeaf IntLeaf::addMod(const IntLeaf & leaf, const IntLeaf & mod) const
{
	//Copy this object, add leaf modulo mod and return the result.
	return IntLeaf(*this).addToMod(leaf, mod);
}


IntLeaf & IntLeaf::operator+=(const IntLeaf & leaf)
{
	//Same as calling addTo(leaf)
    return addTo(leaf);
}


IntLeaf IntLeaf::operator+(const IntLeaf & leaf) const
{
	//Same as calling add(leaf)
    return add(leaf);
}


IntLeaf & IntLeaf::multTo(const IntLeaf & leaf)
{
	//Multiply the data with the data of leaf.
	data *= leaf.data;

	//Return a reference to this object.
    return *this;
}


IntLeaf IntLeaf::mult(const IntLeaf & leaf) const
{
	//Create a copy of this object, multiply it by leaf and return the result.
    return IntLeaf(*this) *= leaf;
}

IntLeaf &IntLeaf::multToMod(const IntLeaf &leaf, const IntLeaf &mod)
{
	//Multiply the current object with leaf
    (*this) *= leaf;

	//Modulo mod
    data %= mod.data;

	//Return a reference to this object.
    return *this;
}


IntLeaf IntLeaf::multMod(const IntLeaf &leaf, const IntLeaf &mod) const
{
	//Copy this object, multiply it by leaf, modulo mod and return the result
	return IntLeaf(*this).multToMod(leaf, mod);
}


IntLeaf & IntLeaf::operator*=(const IntLeaf & leaf)
{
	//Same as calling multTo(leaf)
    return multTo(leaf);
}


IntLeaf IntLeaf::operator*(const IntLeaf & leaf) const
{
	//Same as calling mult(leaf)
    return mult(leaf);
}


IntLeaf &IntLeaf::expTo(unsigned long exponent)
{
	//Raise data to exponent
    mpz_pow_ui(data.get_mpz_t(), data.get_mpz_t(), exponent);

	//Return a reference to this object.
    return *this;
}


IntLeaf IntLeaf::exp(unsigned long exponent) const
{
	//Copy this object, raise it to exponent and return the result
	return IntLeaf(*this).expTo(exponent);
}

IntLeaf &IntLeaf::expToMod(const IntLeaf & leaf, const IntLeaf & mod)
{
	//Raise data to leaf with modulo mod
    length = mod.getLength();
    mpz_powm(data.get_mpz_t(), data.get_mpz_t(), leaf.data.get_mpz_t(), mod.data.get_mpz_t());

	//Return a reference to this object.
    return *this;
}


IntLeaf IntLeaf::expMod(const IntLeaf & leaf, const IntLeaf & mod) const
{
	//Copy this object, raise to leaf, modulo mod and return the result.
	return IntLeaf(*this).expToMod(leaf, mod);
}


bool IntLeaf::operator==(const IntLeaf &leaf) const
{
	//Call the operator== of mpz_class and check if they are the same number
    return (data == leaf.data);
}


bool IntLeaf::operator!=(const IntLeaf &leaf) const
{
	//Same as !(a==b)
    return !(*this == leaf);
}

bool IntLeaf::operator<(const IntLeaf &leaf) const
{
	//Call the operator< of mpz_class
    return data < leaf.data;
}

bool IntLeaf::operator>(const IntLeaf &leaf) const
{
	//Same as !(a < b ||a == b)
    return !(*this < leaf || *this == leaf);
}

IntLeaf IntLeaf::operator-(void) const {
	//Same as -1 * a;
	return (*this) * -1;
}

IntLeaf IntLeaf::inverse(const IntLeaf &mod) const
{
	//Prepare the result
    mpz_class res;

    if(mpz_invert(res.get_mpz_t(), data.get_mpz_t(), mod.getBigInt().get_mpz_t()) == 0)
    {
		//TODO
        // throw exception?
		throw 1;
    }

	//Cast to IntLeaf and return the result
    return IntLeaf(res);
} 


mpz_class IntLeaf::getBigInt(void) const
{
    return data; //Simply return the mpz_class object
}

unsigned int IntLeaf::getBitLength(void) const {
    return mpz_sizeinbase(data.get_mpz_t(), 2);
}

bytevector IntLeaf::toVector(void) const 
{
    //Number of bytes needed for bigint
    unsigned int size = mpz_sizeinbase(data.get_mpz_t(), 256);
    
	//Prepare result vector with zeros
    bytevector bytevec(getLength(), 0);

    //Export the number, starting as far right as possible, ie. left padding with zeros.
    mpz_export(bytevec.data() + (getLength() - size), NULL, ARRAYORDER, sizeof(bytevec[0]), ENDIAN, NAILS, data.get_mpz_t());

    //Check if negative
    bool negative = (mpz_sgn(data.get_mpz_t()) == -1);

    if(negative)
    {
		//Change to corresponding negative number using two's complement
		for(unsigned int i=0; i < bytevec.size(); i++)
		{
			//Flip all bits
			bytevec[i] ^= 0xFF;
		}

		//Fix sign byte
		if(ARRAYORDER == 1) {
			bytevec[bytevec.size() - 1]++;
		} else {
			bytevec[0]++;
		}
    }

	//Return result
    return bytevec;
}


int32_t IntLeaf::getLength(void) const
{
    //This happens if IntLeaf was not constructed from file or byte vector
    if(length == 0) {
		//Get the minimum size needed.
		return mpz_sizeinbase(data.get_mpz_t(), 256);
    } else {
		//Return the set length.
		return length;
    }
}

IntLeaf IntLeaf::div(const IntLeaf &leaf) const {
    mpz_class res = data/leaf.data;
    return (IntLeaf)res;
}

IntLeaf IntLeaf::operator/(const IntLeaf &leaf) const {
    return div(leaf);
}

IntLeaf IntLeaf::sub(const IntLeaf &leaf) const {
    return *this + (-leaf);
}

IntLeaf IntLeaf::operator-(const IntLeaf &leaf) const {
    return sub(leaf);
}


std::string IntLeaf::toString(void) const
{
    return data.get_str(); //Simply return the mpz_class as a string.
}



