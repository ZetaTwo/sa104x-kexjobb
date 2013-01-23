#pragma once
#include "BaseLeaf.h"

#include <gmp.h>
#include <gmpxx.h>

#include <string>

class IntLeaf :
	public BaseLeaf
{
public:
	IntLeaf(void);
	explicit IntLeaf(std::vector<char> bytevec);
	~IntLeaf(void);

	IntLeaf &add(const IntLeaf &leaf);

	IntLeaf &operator=(const IntLeaf &leaf);

	IntLeaf &addTo(const IntLeaf &leaf);
	IntLeaf add(const IntLeaf &leaf) const;

	IntLeaf &operator+=(const IntLeaf &leaf);
	IntLeaf operator+(const IntLeaf &leaf) const;

	IntLeaf &multTo(const IntLeaf &leaf);
	IntLeaf mult(const IntLeaf &leaf) const;

	IntLeaf &operator*=(const IntLeaf &leaf);
	IntLeaf operator*(const IntLeaf &leaf) const;
	
	bool operator==(const IntLeaf &leaf) const;

	virtual std::vector<char> toVector(void) const;
	virtual int32_t getLength(void) const;

	std::string toString(void) const;

private:
	mpz_class data;
};

