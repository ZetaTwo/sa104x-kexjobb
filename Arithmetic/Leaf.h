#pragma once
#include "basenode.h"
class Leaf :
	public BaseNode
{
public:
	Leaf(int32_t length);
	~Leaf(void);

	char &operator[](int32_t index) const;
	char *getData(void) const;
private:
	char *data;
};

