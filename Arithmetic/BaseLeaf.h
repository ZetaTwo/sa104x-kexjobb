#pragma once
#include "basenode.h"

#include <vector>

class BaseLeaf :
	public BaseNode
{
public:
	explicit BaseLeaf(BaseLeaf::NodeType type);
	~BaseLeaf(void);
};

