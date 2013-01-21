#pragma once
#include "basenode.h"

#include <vector>

class Leaf :
	public BaseNode
{
public:
	explicit Leaf(int32_t length);
	~Leaf(void);

	char &operator[](int32_t index);
	const char &operator[](int32_t index) const;
	const std::vector<char> getData(void) const;
private:
	std::vector<char> data;
};

