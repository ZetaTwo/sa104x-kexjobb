#pragma once

#include "basenode.h"

#include <vector>

class Node :
	public BaseNode
{
public:
	explicit Node(int32_t length);
	~Node(void);

	BaseNode* const &operator[](int32_t index) const;
	BaseNode* &operator[](int32_t index);
private:
	std::vector<BaseNode *> children;
};

