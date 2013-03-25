#pragma once

#include "BaseNode.h"
#include "IntLeaf.h"

#include <vector>
#include <fstream>
#include <string>

class Node :
	public BaseNode
{
public:
	Node(void);
	Node(const Node &node);
	Node(const bytevector data);
	explicit Node(const std::string filename);
	explicit Node(std::istream &file);
	~Node(void);

	static Node *constructPartFromFile(std::istream &file, uint32_t count);

	virtual bytevector toVector(void) const;

	Node &operator=(const Node &node);

	Node &modTo(const IntLeaf &leaf);
	Node mod(const IntLeaf &leaf) const;

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
	Node expMod(const IntLeaf &exponent, const IntLeaf &mod) const;
	Node exp(const Node &exponents) const;
	Node expMod(const Node &exponents, const IntLeaf &mod) const;
	Node &expTo(unsigned long exponent);
	Node &expToMod(unsigned long exponent, const IntLeaf &mod);
	Node &expToMod(const IntLeaf &exponent, const IntLeaf &mod);
	Node &expTo(const Node &exponents);
	Node &expToMod(const Node &exponents, const IntLeaf &mod);

	IntLeaf expMultMod(const Node &node, const IntLeaf &mod) const;
	IntLeaf expMult(unsigned long exponent) const;
	IntLeaf expMultMod(unsigned long exponent, const IntLeaf &mod) const;

	Node &addChild(const BaseNode &child);
	Node getChildren(int32_t index) const;

	IntLeaf &getIntLeafChild(int32_t index);
	const IntLeaf &getIntLeafChild(int32_t index) const;

	Node &getNodeChild(int32_t index);
	const Node &getNodeChild(int32_t index) const;

	std::string toString(void) const;

	virtual int32_t getLength(void) const;
private:
	BaseNode &getChild(int32_t index);
	const BaseNode &getChild(int32_t index) const;

	std::vector<BaseNode *> children;

	void constructFromFilename(const std::string filename);
	void constructFromFile(std::istream &file);
	void constructChildrenFromFile(std::istream &file, uint32_t count);

	void copyElements(std::vector<BaseNode *> elements);
	void clearElements();
};
