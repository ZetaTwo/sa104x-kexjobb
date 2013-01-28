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

	Node &addTo(const Node &node);
	Node add(const Node &node) const;

	Node &addToMod(const IntLeaf &leaf, const IntLeaf &mod);
	Node addMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	Node &addToMod(const Node &node, const IntLeaf &mod);
	Node addMod(const Node &node, const IntLeaf &mod) const;

	Node &operator+=(const IntLeaf &leaf);
	Node operator+(const IntLeaf &leaf) const;

	Node &operator+=(const Node &node);
	Node operator+(const Node &node) const;

	Node &multTo(const IntLeaf &leaf);
	Node mult(const IntLeaf &leaf) const;

	Node &multTo(const Node &node);
	Node mult(const Node &node) const;

	Node &multToMod(const IntLeaf &leaf, const IntLeaf &mod);
	Node multMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	Node &multToMod(const Node &node, const IntLeaf &mod);
	Node multMod(const Node &node, const IntLeaf &mod) const;

	Node &operator*=(const IntLeaf &leaf);
	Node operator*(const IntLeaf &leaf) const;

	Node &operator*=(const Node &node);
	Node operator*(const Node &node) const;
	
	bool operator==(const Node &node) const;
	bool operator!=(const Node &node) const;

	IntLeaf sum(void) const;
	IntLeaf sumMod(const IntLeaf &mod) const;

	IntLeaf prod(void) const;
	IntLeaf prodMod(const IntLeaf &mod) const;

	Node exp(unsigned long exponent) const;
	Node expMod(unsigned long exponent, const IntLeaf &mod) const;
	Node exp(const Node &exponents) const;
	Node expMod(const Node &exponents, const IntLeaf &mod) const;
	Node &expTo(unsigned long exponent) const;
	Node &expModTo(unsigned long exponent, const IntLeaf &mod) const;
	Node &expTo(const Node &exponents) const;
	Node &expModTo(const Node &exponents, const IntLeaf &mod) const;

	IntLeaf expMultMod(const Node &node, const IntLeaf &mod) const;
	IntLeaf expMult(unsigned long exponent) const;
	IntLeaf expMultMod(unsigned long exponent, const IntLeaf &mod) const;

	Node &addChild(const BaseNode &child);
	std::string toString(void) const;

	virtual int32_t getLength(void) const;
private:
	std::vector<BaseNode *> children;
};
