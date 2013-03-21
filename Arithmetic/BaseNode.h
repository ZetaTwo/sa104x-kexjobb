#pragma once

#include <vector>
#include <stdint.h>
#include <istream>

class BaseNode
{
public:
	enum NodeType { NODE = 0, INT_LEAF = 1, DATA_LEAF = 2 };

	BaseNode(BaseNode::NodeType type);
	~BaseNode(void);

	BaseNode::NodeType getType(void) const;
	virtual int32_t getLength(void) const = 0;
	virtual std::vector<unsigned char> toVector(void) const = 0;
	std::vector<unsigned char> serialize() const;
	std::vector<unsigned char> concatData(const BaseNode * const other) const;


private:
	const BaseNode::NodeType type;

protected:
	static BaseNode *copy(const BaseNode *node);
	static void ReadNodeHeader(std::istream &file, char &type, uint32_t &length);
};

