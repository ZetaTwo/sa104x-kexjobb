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

//Node Node::operator+(const IntLeaf &leaf) const;

Node &Node::multTo(const IntLeaf &leaf) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->multTo(leaf);
	}

	return *this;	
};

//Node Node::mult(const IntLeaf &leaf) const;

Node &Node::multToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->multToMod(leaf, mod);
	}

	return *this;	
};

//Node Node::multMod(const IntLeaf &leaf, const IntLeaf &mod) const;

Node &Node::operator*=(const IntLeaf &leaf) {
	return multTo(leaf);	
};

//Node Node::operator*(const IntLeaf &leaf) const;
	
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

IntLeaf Node::exp(unsigned long exponent) const {
	IntLeaf exp;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		exp.expTo(*static_cast<IntLeaf *>(*itr));
	}

	return exp;
};
IntLeaf Node::expMod(unsigned long exponent, const IntLeaf &mod) const {
	IntLeaf exp;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		exp.expToMod(*static_cast<IntLeaf *>(*itr), mod);
	}

	return exp;
};

Node Node::expMult(const Node &leaf) const {
	//TODO
	Node result;

	return result;
};
Node Node::expMultMod(const Node &leaf, const IntLeaf &mod) const {
	//TODO
	Node result;

	return result;
};