#pragma once
#include "BaseLeaf.h"

#include <gmp.h>
#include <gmpxx.h>

#include <string>
#include <fstream>

class IntLeaf :
	public BaseLeaf
{
public:
    static const int ARRAYORDER = 1; /* -1 for least significant byte first, 1 for most significant byte first */
    static const int ENDIAN = 0;
    static const int NAILS = 0;

    IntLeaf(void);
    IntLeaf(const IntLeaf &leaf);
    IntLeaf(long int input);
	IntLeaf(long int input, long int length);
    explicit IntLeaf(std::string input);
    explicit IntLeaf(std::vector<unsigned char> bytevec);
    explicit IntLeaf(std::istream &file);
    ~IntLeaf(void);

    static BaseNode *constructPartFromFile(std::istream &file, uint32_t length);

    IntLeaf &operator=(const IntLeaf &leaf);
    IntLeaf &operator=(long int input);
    IntLeaf &operator=(std::string input);	
    
    IntLeaf &addTo(const IntLeaf &leaf);
    IntLeaf add(const IntLeaf &leaf) const;
    
    IntLeaf &addToMod(const IntLeaf &leaf, const IntLeaf &mod);
    IntLeaf addMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
    IntLeaf &operator+=(const IntLeaf &leaf);
    IntLeaf operator+(const IntLeaf &leaf) const;
    
    IntLeaf &multTo(const IntLeaf &leaf);
    IntLeaf mult(const IntLeaf &leaf) const;
    
    IntLeaf &multToMod(const IntLeaf &leaf, const IntLeaf &mod);
    IntLeaf multMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
    IntLeaf &operator*=(const IntLeaf &leaf);
    IntLeaf operator*(const IntLeaf &leaf) const;

    IntLeaf &expTo(unsigned long exponent);
    IntLeaf exp(unsigned long exponent) const;
    
    IntLeaf &expToMod(const IntLeaf &leaf, const IntLeaf &mod);
    IntLeaf expMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
    bool operator==(const IntLeaf &leaf) const;
    bool operator!=(const IntLeaf &leaf) const;

    bool operator<(const IntLeaf &leaf) const;
    bool operator>(const IntLeaf &leaf) const;

	IntLeaf operator-() const;
    
    mpz_class getBigInt(void) const;
    virtual std::vector<unsigned char> toVector(void) const;
    virtual int32_t getLength(void) const;
    
    std::string toString(void) const;
	
private:
    mpz_class data;
    uint32_t length;
};

