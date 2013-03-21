#pragma once

#include <stdint.h>
#include <istream>

#include "types.h"

class BaseNode
{
public:
	enum NodeType { NODE = 0, INT_LEAF = 1, DATA_LEAF = 2 };

	BaseNode(BaseNode::NodeType type);
	~BaseNode(void);

	BaseNode::NodeType getType(void) const;
	virtual int32_t getLength(void) const = 0;
	virtual bytevector toVector(void) const = 0;
	bytevector serialize() const;
	bytevector concatData(const BaseNode * const other) const;


private:
	const BaseNode::NodeType type;

protected:
	static BaseNode *copy(const BaseNode *node);
	static void ReadNodeHeader(std::istream &file, char &type, uint32_t &length);
};

