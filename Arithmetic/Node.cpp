#include "Node.h"
#include "DataLeaf.h"

#include <stdexcept>

Node::Node() : BaseNode(BaseNode::NODE)
{
}

Node::Node(const Node &node) : BaseNode(BaseNode::NODE)
{
	for (std::vector<BaseNode *>::const_iterator itr = node.children.begin(); itr < node.children.end(); itr++)
	{
		NodeType type = (*itr)->getType();
		BaseNode *element;
		switch(type) {
		case NodeType::INT_LEAF:
			element = new IntLeaf(*static_cast<IntLeaf *>(*itr));
			break;
		case NodeType::NODE:
			element = new Node(*static_cast<Node *>(*itr));
			break;
		case NodeType::DATA_LEAF:
			element = new DataLeaf(*static_cast<DataLeaf *>(*itr));
			break;
		default:
			break;
		}

		children.push_back(element);
	}
}

Node::~Node(void)
{
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		delete *itr;
	}
}

std::vector<char> Node::toVector(void) const {
	return std::vector<char>();
};

int32_t Node::getLength(void) const {
	return children.size();
};

Node &Node::operator=(const Node &node) {
	if(*this != node) {
		children = node.children;	
	}

	return *this;
};

Node &Node::addTo(const IntLeaf &leaf) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->addTo(leaf);
	}

	return *this;
};

Node Node::add(const IntLeaf &leaf) const {
	return *this;
};

Node &Node::addToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->addToMod(leaf, mod);
	}

	return *this;
};
Node Node::addMod(const IntLeaf &leaf, const IntLeaf &mod) const {
	return *this;
};

Node &Node::operator+=(const IntLeaf &leaf) {
	return addTo(leaf);
};

Node Node::operator+(const IntLeaf &leaf) const {
	return add(leaf);
}

Node &Node::multTo(const IntLeaf &leaf) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->multTo(leaf);
	}

	return *this;	
};

Node Node::mult(const IntLeaf &leaf) const {
	Node mult;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		mult.addChild(static_cast<IntLeaf *>(*itr)->mult(leaf));
	}

	return mult;
};

Node &Node::multToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->multToMod(leaf, mod);
	}

	return *this;	
};

Node Node::multMod(const IntLeaf &leaf, const IntLeaf &mod) const {
	Node mult;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		mult.addChild(static_cast<IntLeaf *>(*itr)->multMod(leaf, mod));
	}

	return mult;
}

Node &Node::operator*=(const IntLeaf &leaf) {
	return multTo(leaf);	
};

Node Node::operator*(const IntLeaf &leaf) const {
	return mult(leaf);	
}
	
bool Node::operator==(const Node &leaf) const {
	return (this->children == leaf.children);
};

bool Node::operator!=(const Node &leaf) const {
	return !(*this == leaf);	
};

IntLeaf Node::sum(void) const {
	IntLeaf sum;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		sum.addTo(*static_cast<IntLeaf *>(*itr));
	}

	return sum;
};
IntLeaf Node::sumMod(const IntLeaf &mod) const {
	IntLeaf sum;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		sum.addToMod(*static_cast<IntLeaf *>(*itr), mod);
	}

	return sum;
};

IntLeaf Node::prod(void) const {
	IntLeaf prod;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		prod.multTo(*static_cast<IntLeaf *>(*itr));
	}

	return prod;
};
IntLeaf Node::prodMod(const IntLeaf &mod) const {
	IntLeaf prod;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		prod.multToMod(*static_cast<IntLeaf *>(*itr), mod);
	}

	return prod;
};

Node Node::exp(unsigned long exponent) const {
	Node exp;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		exp.addChild(static_cast<IntLeaf *>(*itr)->exp(exponent));
	}

	return exp;
};

Node Node::expMod(unsigned long exponent, const IntLeaf &mod) const {
	Node exp;
	
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		exp.addChild(static_cast<IntLeaf *>(*itr)->expMod(exponent, mod));
	}

	return exp;
};

IntLeaf Node::expMult(const Node &node) const {
	IntLeaf result;

	for (std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
		itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
	{
		result.addTo(static_cast<IntLeaf *>(*itr1)->exp(*static_cast<IntLeaf *>(*itr2)));
	}

	return result;
};
IntLeaf Node::expMultMod(const Node &node, const IntLeaf &mod) const {
	IntLeaf result;

	for (std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
		itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
	{
		result.addToMod(static_cast<IntLeaf *>(*itr1)->expMod(*static_cast<IntLeaf *>(*itr2), mod), mod);
	}

	return result;
};

IntLeaf Node::expMult(unsigned long exp) const {
	IntLeaf result;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		result.addTo(static_cast<IntLeaf *>(*itr)->exp(exp));
	}

	return result;
};
IntLeaf Node::expMultMod(const unsigned long exp, const IntLeaf &mod) const {
	IntLeaf result;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		result.addToMod(static_cast<IntLeaf *>(*itr)->expMod(exp, mod), mod);
	}

	return result;
};