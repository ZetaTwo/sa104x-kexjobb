#pragma once

#include <vector>
#include <stdint.h>

class BaseNode
{
public:
	enum NodeType { NODE = 0, INT_LEAF = 1, DATA_LEAF = 2 };

	BaseNode(BaseNode::NodeType type);
	~BaseNode(void);

	BaseNode::NodeType getType(void) const;
	virtual int32_t getLength(void) const = 0;
	virtual std::vector<char> toVector(void) const = 0;

private:
	const BaseNode::NodeType type;
};

