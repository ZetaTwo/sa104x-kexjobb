#pragma once
#include "basenode.h"

#include <vector>

class BaseLeaf :
	public BaseNode
{
public:
	BaseLeaf(void);
	explicit BaseLeaf(BaseLeaf::NodeType type);
	~BaseLeaf(void);

	virtual std::vector<char> toVector(void) const = 0;
};

