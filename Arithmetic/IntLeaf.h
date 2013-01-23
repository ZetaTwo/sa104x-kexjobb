#pragma once
#include "baseleaf.h"
class IntLeaf :
	public BaseLeaf
{
public:
	IntLeaf(void);
	~IntLeaf(void);

	IntLeaf &operator=(const IntLeaf &leaf);

	IntLeaf &operator+=(const IntLeaf &leaf);
	IntLeaf operator+(const IntLeaf &leaf) const;

	IntLeaf &operator*=(const IntLeaf &leaf);
	IntLeaf operator*(const IntLeaf &leaf) const;
	
	bool operator==(const IntLeaf &leaf) const;

	virtual std::vector<char> toVector(void) const;
	virtual int32_t getLength(void) const;
};

