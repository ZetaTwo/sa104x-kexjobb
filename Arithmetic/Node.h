#pragma once

#include "basenode.h"

#include <vector>

class Node :
	public BaseNode
{
public:
	explicit Node(void);
	~Node(void);

	BaseNode* const &operator[](int32_t index) const;
	BaseNode* &operator[](int32_t index);

	virtual int32_t getLength(void) const;
private:
	std::vector<BaseNode *> children;
};

