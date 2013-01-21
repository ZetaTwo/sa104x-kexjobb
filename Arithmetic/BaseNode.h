#pragma once

#include <stdint.h>

class BaseNode
{
public:
	enum NodeType { NODE = 0, LEAF = 1 };

	BaseNode(void);
	BaseNode(BaseNode::NodeType type, int32_t length);
	~BaseNode(void);

	char getType(void) const;
	int32_t getLength(void) const;

private:
	const char type;
	const int32_t length;
};

