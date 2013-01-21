#pragma once

#include "basenode.h"


class Node :
	public BaseNode
{
public:
	Node(int32_t length);
	~Node(void);

	BaseNode *&operator[](int32_t index) const;
private:
	BaseNode **children;
};

