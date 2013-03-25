#include "Node.h"
#include "DataLeaf.h"

#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <iterator>
#include <iostream>

Node::Node() : BaseNode(BaseNode::NODE)
{
}

Node::Node(const Node &node) : BaseNode(BaseNode::NODE)
{
	copyElements(node.children);
}

Node::Node(const bytevector data) : BaseNode(BaseNode::NODE) {
	std::stringstream ioss;    
	std::copy(data.begin(), data.end(), std::ostream_iterator<char>(ioss, ""));
	constructFromFile(ioss);
}

Node::Node(const std::string filename) : BaseNode(BaseNode::NODE) {
	constructFromFilename(filename);
}

Node::Node(std::istream &file) : BaseNode(BaseNode::NODE) {
	constructFromFile(file);
}

void Node::constructFromFilename(const std::string filename) {
	std::ifstream file(filename.c_str(), std::fstream::in);
	constructFromFile(file);
}
void Node::constructFromFile(std::istream &file) {
	char type;
	uint32_t count;
	ReadNodeHeader(file, type, count);

	constructChildrenFromFile(file, count);
}

Node *Node::constructPartFromFile(std::istream &file, uint32_t count) {
	Node *result = new Node();
	result->constructChildrenFromFile(file, count);

	return result;
}

void Node::constructChildrenFromFile(std::istream &file, uint32_t count) {
	Node *result = new Node();
	for (uint32_t i = 0; i < count; i++)
	{
		char type;
		uint32_t childCount;
		ReadNodeHeader(file, type, childCount);

		if(type == 0) {
			addChild(*Node::constructPartFromFile(file, childCount));
		} else if(type == 1) {
			addChild(*IntLeaf::constructPartFromFile(file, childCount));
		} else {
			break;
		}
	}
}

Node::~Node(void)
{
	
}

int32_t Node::getLength(void) const {
	return children.size();
};

Node &Node::operator=(const Node &node) {
	if(*this != node) {
		clearElements();
		copyElements(node.children);	
	}

	return *this;
};


Node &Node::modTo(const IntLeaf &leaf) {
    for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
    {
	switch((*itr)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr)->modTo(leaf);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr)->modTo(leaf);
	    break;
	default:
	    break;
	}
    }
    
    return *this;
}


Node Node::mod(const IntLeaf &leaf) const {
    Node *result = new Node(*this);
    result->modTo(leaf);
    
    return *result;
};


Node &Node::addTo(const IntLeaf &leaf) {
    for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
    {
	switch((*itr)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr)->addTo(leaf);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr)->addTo(leaf);
	    break;
	default:
	    break;
	}
    }
    
    return *this;
};

Node &Node::addTo(const Node &node) {
    for (std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
	 itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
    {
	switch((*itr1)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr1)->addTo(*static_cast<IntLeaf *>(*itr2));
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr1)->addTo(*static_cast<Node *>(*itr2));
	    break;
	default:
	    break;
	}
    }

    return *this;
}


Node Node::add(const IntLeaf &leaf) const {
    Node *result = new Node(*this);
    result->addTo(leaf);
    
    return *result;
};


Node Node::add(const Node &node) const {
    Node result(*this);
    result.addTo(node);
    
    return result;
}


Node &Node::addToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			static_cast<IntLeaf *>(*itr)->addToMod(leaf, mod);
			break;
		case BaseNode::NODE:
			static_cast<Node *>(*itr)->addToMod(leaf, mod);
			break;
		default:
			break;
		}
	}

	return *this;
};


Node &Node::addToMod(const Node &node, const IntLeaf &mod) {
    for (std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
	 itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
    {
	switch((*itr1)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr1)->addToMod(*static_cast<IntLeaf *>(*itr2), mod);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr1)->addToMod(*static_cast<Node *>(*itr2), mod);
	    break;
	default:
	    break;
	}
    }

    return *this;
}

Node Node::addMod(const IntLeaf &leaf, const IntLeaf &mod) const {
    Node result(*this);
    result.addToMod(leaf, mod);
    
    return result;
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
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			static_cast<IntLeaf *>(*itr)->multTo(leaf);
			break;
		case BaseNode::NODE:
			static_cast<Node *>(*itr)->multTo(leaf);
			break;
		default:
			break;
		}
	}

	return *this;	
};


Node &Node::multTo(const Node &node) {
    for (std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
	 itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
    {
	switch((*itr1)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr1)->multTo(*static_cast<IntLeaf *>(*itr2));
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr1)->multTo(*static_cast<Node *>(*itr2));
	    break;
	default:
	    break;
	}
    }

    return *this;
}

Node Node::mult(const IntLeaf &leaf) const {
	Node mult;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			mult.addChild(static_cast<IntLeaf *>(*itr)->mult(leaf));
			break;
		case BaseNode::NODE:
			mult.addChild(static_cast<Node *>(*itr)->mult(leaf));
			break;
		default:
			break;
		}
	}

	return mult;
};

Node Node::mult(const Node &node) const {
    Node result(*this);
    result.multTo(node);

    return result;
}

Node &Node::multToMod(const IntLeaf &leaf, const IntLeaf &mod) {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			static_cast<IntLeaf *>(*itr)->multToMod(leaf, mod);
			break;
		case BaseNode::NODE:
			static_cast<Node *>(*itr)->multToMod(leaf, mod);
			break;
		default:
			break;
		}
	}

	return *this;	
};

Node &Node::multToMod(const Node &node, const IntLeaf &mod) {
    for (std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
	 itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
    {
	switch((*itr1)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr1)->multToMod(*static_cast<IntLeaf *>(*itr2), mod);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr1)->multToMod(*static_cast<Node *>(*itr2), mod);
	    break;
	default:
	    break;
	}
    }

    return *this;
}

Node Node::multMod(const IntLeaf &leaf, const IntLeaf &mod) const {
	Node mult;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			mult.addChild(static_cast<IntLeaf *>(*itr)->multMod(leaf, mod));
			break;
		case BaseNode::NODE:
			mult.addChild(static_cast<Node *>(*itr)->multMod(leaf, mod));
			break;
		default:
			break;
		}
	}

	return mult;
}

Node Node::multMod(const Node &node, const IntLeaf &mod) const {
    Node result(*this);
    result.multToMod(node, mod);

    return result;
}

Node &Node::operator*=(const IntLeaf &leaf) {
	return multTo(leaf);	
}

Node Node::operator*(const IntLeaf &leaf) const {
	return mult(leaf);	
}

Node &Node::operator*=(const Node &node) {
	return multTo(node);	
}

Node Node::operator*(const Node &node) const {
	return mult(node);	
}
	
bool Node::operator==(const Node &node) const {

	if(getLength() != node.getLength()) {
		return false;
	}

    for(std::vector<BaseNode *>::const_iterator itr1 = children.begin(), itr2 = node.children.begin();
		itr1 < children.end() && itr2 < node.children.end() ; itr1++, itr2++)
    {
		switch((*itr1)->getType()) {
		case BaseNode::INT_LEAF:
			if(!static_cast<IntLeaf *>(*itr1)->operator==(*static_cast<IntLeaf *>(*itr2)))
			{
				return false;
			}
			break;
		case BaseNode::NODE:
			if(!static_cast<Node *>(*itr1)->operator==(*static_cast<Node *>(*itr2)))
			{
				return false;
			}
			break;
		default:
			break;
		}
    }

    return true;
};

bool Node::operator!=(const Node &node) const {
	return !(*this == node);	
};

IntLeaf Node::sum(void) const {
	IntLeaf sum;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			sum.addTo(*static_cast<IntLeaf *>(*itr));
			break;
		case BaseNode::NODE:
			sum.addTo(static_cast<Node *>(*itr)->sum());
			break;
		default:
			break;
		}

		sum.addTo(*static_cast<IntLeaf *>(*itr));
	}

	return sum;
};
IntLeaf Node::sumMod(const IntLeaf &mod) const {
	IntLeaf sum;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			sum.addToMod(*static_cast<IntLeaf *>(*itr), mod);
			break;
		case BaseNode::NODE:
			sum.addToMod(static_cast<Node *>(*itr)->sum(), mod);
			break;
		default:
			break;
		}
	}

	return sum;
};

IntLeaf Node::prod(void) const {
	IntLeaf prod;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			prod.multTo(*static_cast<IntLeaf *>(*itr));
			break;
		case BaseNode::NODE:
			prod.multTo(static_cast<Node *>(*itr)->prod());
			break;
		default:
			break;
		}
	}

	return prod;
};
IntLeaf Node::prodMod(const IntLeaf &mod) const {
	IntLeaf prod;
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			prod.multToMod(*static_cast<IntLeaf *>(*itr), mod);
			break;
		case BaseNode::NODE:
			prod.multToMod(static_cast<Node *>(*itr)->prodMod(mod), mod);
			break;
		default:
			break;
		}
	}

	return prod;
};

Node &Node::expTo(unsigned long exponent) {

    for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
	switch((*itr)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr)->expTo(exponent);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr)->expTo(exponent);
	    break;
	default:
	    break;
	}
    }

    return *this;

}

Node Node::exp(unsigned long exponent) const {
    Node exp(*this);

    return exp.expTo(exponent);
};

Node &Node::expToMod(unsigned long exponent, const IntLeaf &mod) {
    for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
	switch((*itr)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr)->expToMod(exponent, mod);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr)->expToMod(exponent, mod);
	    break;
	default:
	    break;
	}
    }

    return *this;
}

Node Node::expMod(unsigned long exponent, const IntLeaf &mod) const {
    Node exp(*this);

    return exp.expToMod(exponent, mod);
};

Node &Node::expToMod(const IntLeaf &exponent, const IntLeaf &mod) {
    for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
	switch((*itr)->getType()) {
	case BaseNode::INT_LEAF:
	    static_cast<IntLeaf *>(*itr)->expToMod(exponent, mod);
	    break;
	case BaseNode::NODE:
	    static_cast<Node *>(*itr)->expToMod(exponent, mod);
	    break;
	default:
	    break;
	}
    }

    return *this;
}

Node Node::expMod(const IntLeaf &exponent, const IntLeaf &mod) const {
    Node exp(*this);
    return exp.expToMod(exponent, mod);
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

bytevector Node::toVector(void) const {
    bytevector res;

    for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
		bytevector nextelem = (*itr)->serialize();
		res.insert(res.end(), nextelem.begin(), nextelem.end());
    }
    
    return res;
}


std::string Node::toString(void) const {
    std::string res = "(";

    for(std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			res += static_cast<IntLeaf *>(*itr)->toString();
			break;
		case BaseNode::NODE:
			res += static_cast<Node *>(*itr)->toString();
			break;
		default:
			break;
		}

		if(itr < children.end()-1) {
			res += ", ";
		}
    }

    return res + ")";
}

Node &Node::addChild(const BaseNode &child) {
	BaseNode *node = copy(&child);
	children.push_back(node);
	return *this;
}

BaseNode &Node::getChild(int32_t index) {
	return *children[index];
}

const BaseNode &Node::getChild(int32_t index) const {
    return *children[index];
}

IntLeaf &Node::getIntLeafChild(int32_t index) {
    return static_cast<IntLeaf &>(getChild(index));
}

const IntLeaf &Node::getIntLeafChild(int32_t index) const {
    return static_cast<const IntLeaf &>(getChild(index));
}

Node &Node::getNodeChild(int32_t index) {
    return static_cast<Node &>(getChild(index));
}

const Node &Node::getNodeChild(int32_t index) const {
    return static_cast<const Node &>(getChild(index));
}

Node Node::getChildren(int32_t index) const {
    Node res;

    for(std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
        res.addChild(static_cast<const Node *>(*itr)->getChild(index));
    }

    return res;
}

void Node::copyElements(std::vector<BaseNode *> elements) {
	for (std::vector<BaseNode *>::const_iterator itr = elements.begin(); itr < elements.end(); itr++)
	{
		BaseNode *element = copy(*itr);
		children.push_back(element);
	}
}

void Node::clearElements() {
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
	    delete *itr;
	}
}
