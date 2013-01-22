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

	virtual int32_t getLength(void) const;
private:
	std::vector<char> data;
};

