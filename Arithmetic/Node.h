#pragma once

#include "BaseNode.h"
#include "IntLeaf.h"

#include <vector>

class Node :
	public BaseNode
{
public:
	Node(void);
	Node(const Node &node);
	~Node(void);

	virtual std::vector<char> toVector(void) const;

	Node &operator=(const Node &node);

	Node &addTo(const IntLeaf &leaf);
	Node add(const IntLeaf &leaf) const;

	Node &addToMod(const IntLeaf &leaf, const IntLeaf &mod);
	Node addMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	Node &operator+=(const IntLeaf &leaf);
	Node operator+(const IntLeaf &leaf) const;

	Node &multTo(const IntLeaf &leaf);
	Node mult(const IntLeaf &leaf) const;

	Node &multToMod(const IntLeaf &leaf, const IntLeaf &mod);
	Node multMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	Node &operator*=(const IntLeaf &leaf);
	Node operator*(const IntLeaf &leaf) const;
	
	bool operator==(const Node &leaf) const;
	bool operator!=(const Node &leaf) const;

	IntLeaf sum(void) const;
	IntLeaf sumMod(const IntLeaf &mod) const;

	IntLeaf prod(void) const;
	IntLeaf prodMod(const IntLeaf &mod) const;

	IntLeaf exp(unsigned long exponent) const;
	IntLeaf expMod(unsigned long exponent, const IntLeaf &mod) const;

	Node expMult(const Node &leaf) const;
	Node expMultMod(const Node &leaf, const IntLeaf &mod) const;


	std::vector<BaseNode *> &getChildren(void);



	virtual int32_t getLength(void) const;
private:
	std::vector<BaseNode *> children;
};

