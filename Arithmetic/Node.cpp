#include "Node.h"

#include <stdexcept>

Node::Node() : BaseNode(BaseNode::NODE)
{
}

Node::~Node(void)
{
}

Node* const &Node::operator[](int32_t index) const {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return static_cast<Node *>(children[index]);
}

Node* &Node::operator[](int32_t index) {
	if(index >= getLength() || index < 0) {
		throw std::out_of_range("Index is out of range");
	}

	return static_cast<Node *>(children[index]);
}

std::vector<BaseNode *> &Node::getChildren(void) {
	return children;
}

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

};

Node &Node::addToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->addToMod(leaf, mod);
	}

	return *this;
};
Node Node::addMod(const IntLeaf &leaf, const IntLeaf &mod) const {

};

Node &Node::operator+=(const IntLeaf &leaf) {
	return addTo(leaf);
};

Node Node::operator+(const IntLeaf &leaf) const;

Node &Node::multTo(const IntLeaf &leaf) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->multTo(leaf);
	}

	return *this;	
};
Node Node::mult(const IntLeaf &leaf) const;

Node &Node::multToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		static_cast<IntLeaf *>(*itr)->multToMod(leaf, mod);
	}

	return *this;	
};
Node Node::multMod(const IntLeaf &leaf, const IntLeaf &mod) const;

Node &Node::operator*=(const IntLeaf &leaf) {
	return multTo(leaf);	
};
Node Node::operator*(const IntLeaf &leaf) const;
	
bool Node::operator==(const Node &leaf) const {
	return (this->children == leaf.children);
};

bool Node::operator!=(const Node &leaf) const {
	return !(*this == leaf);	
};

IntLeaf Node::sum(const IntLeaf &leaf) const {
	IntLeaf sum;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		sum.addTo(*static_cast<IntLeaf *>(*itr));
	}

	return sum;
};
IntLeaf Node::sumMod(const IntLeaf &leaf, const IntLeaf &mod) const {
	IntLeaf sum;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		sum.addToMod(*static_cast<IntLeaf *>(*itr), mod);
	}

	return sum;
};

IntLeaf Node::prod(const IntLeaf &leaf) const {
	IntLeaf prod;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		prod.multTo(*static_cast<IntLeaf *>(*itr));
	}

	return prod;
};
IntLeaf Node::prodMod(const IntLeaf &leaf, const IntLeaf &mod) const {
	IntLeaf prod;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		prod.multToMod(*static_cast<IntLeaf *>(*itr), mod);
	}

	return prod;
};

IntLeaf Node::exp(const IntLeaf &leaf) const {
	IntLeaf exp;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		exp.expTo(*static_cast<IntLeaf *>(*itr));
	}

	return exp;
};
IntLeaf Node::expMod(const IntLeaf &leaf, const IntLeaf &mod) const {
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