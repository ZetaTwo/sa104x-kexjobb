#pragma once

#include "BaseNode.h"
#include "IntLeaf.h"

#include <vector>

class Node :
	public BaseNode
{
public:
	explicit Node(void);
	~Node(void);

	Node *const &operator[](int32_t index) const;
	Node *&operator[](int32_t index);

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

	IntLeaf sum(const IntLeaf &leaf) const;
	IntLeaf sumMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	IntLeaf prod(const IntLeaf &leaf) const;
	IntLeaf prodMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	IntLeaf exp(const IntLeaf &leaf) const;
	IntLeaf expMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	Node expMult(const Node &leaf) const;
	Node expMultMod(const Node &leaf, const IntLeaf &mod) const;


	std::vector<BaseNode *> &getChildren(void);



	virtual int32_t getLength(void) const;
private:
	std::vector<BaseNode *> children;
};

