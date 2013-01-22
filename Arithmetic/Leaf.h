#pragma once
#include "basenode.h"

#include <vector>

class Leaf :
	public BaseNode
{
public:
	explicit Leaf(void);
	~Leaf(void);

	char &operator[](int32_t index);
	const char &operator[](int32_t index) const;
	std::vector<char> &getData(void);
	const std::vector<char> &getData(void) const;

	virtual int32_t getLength(void) const;

	Leaf &operator=(const Leaf &leaf);

	Leaf &operator+=(const Leaf &leaf);
	Leaf operator+(const Leaf &leaf) const;

	Leaf &operator*=(const Leaf &leaf);
	Leaf operator*(const Leaf &leaf) const;
	
	bool operator==(const Leaf &leaf) const;

private:
	std::vector<char> data;
};

