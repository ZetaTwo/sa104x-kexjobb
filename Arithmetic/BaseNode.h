#pragma once

#include <stdint.h>

class BaseNode
{
public:
	enum NodeType { NODE = 0, LEAF = 1 };

	BaseNode(void);
	BaseNode(BaseNode::NodeType type);
	~BaseNode(void);

	char getType(void) const;
	virtual int32_t getLength(void) const = 0;

private:
	const char type;
};

