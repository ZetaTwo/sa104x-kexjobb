#pragma once
#include "BaseLeaf.h"

#include <gmp.h>
#include <gmpxx.h>

#include <string>

class IntLeaf :
	public BaseLeaf
{
public:
	const int ARRAYORDER = 1; /* -1 for least significant byte first, 1 for most significant byte first */
	const int ENDIAN = 0;
	const int NAILS = 0;

	IntLeaf(void);
	explicit IntLeaf(std::vector<char> bytevec);
	~IntLeaf(void);

	IntLeaf &operator=(const IntLeaf &leaf);

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

	IntLeaf &expTo(const IntLeaf &leaf);
	IntLeaf exp(const IntLeaf &leaf) const;

	IntLeaf &expToMod(const IntLeaf &leaf, const IntLeaf &mod);
	IntLeaf expMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	bool operator==(const IntLeaf &leaf) const;
	bool operator!=(const IntLeaf &leaf) const;

	mpz_class getBigInt(void) const;
	virtual std::vector<char> toVector(void) const;
	virtual int32_t getLength(void) const;

	std::string toString(void) const;

private:
	mpz_class data;
};

