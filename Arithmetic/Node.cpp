#include "Node.h"
#include "DataLeaf.h"

Node::Node() : BaseNode(BaseNode::NODE)
{
}

Node::Node(const Node &node) : BaseNode(BaseNode::NODE)
{
	for (std::vector<BaseNode *>::const_iterator itr = node.children.begin(); itr < node.children.end(); itr++)
	{
		BaseNode *element = copy(*itr);
		children.push_back(element);
	}
}

Node::Node(const std::vector<char> data) : BaseNode(BaseNode::NODE) {

}

Node::~Node(void)
{
	for (std::vector<BaseNode *>::iterator itr = children.begin(); itr < children.end(); itr++)
	{
	    delete *itr;
	}
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
    Node result(*this);
    result.addTo(leaf);
    
    return result;
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

Node Node::exp(unsigned long exponent) const {
	Node exp;

	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			exp.addChild(static_cast<IntLeaf *>(*itr)->exp(exponent));
			break;
		case BaseNode::NODE:
			exp.addChild(static_cast<Node *>(*itr)->exp(exponent));
			break;
		default:
			break;
		}
	}

	return exp;
};

Node Node::expMod(unsigned long exponent, const IntLeaf &mod) const {
	Node exp;
	
	for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
	{
		switch((*itr)->getType()) {
		case BaseNode::INT_LEAF:
			exp.addChild(static_cast<IntLeaf *>(*itr)->expMod(exponent, mod));
			break;
		case BaseNode::NODE:
			exp.addChild(static_cast<Node *>(*itr)->expMod(exponent, mod));
			break;
		default:
			break;
		}
	}

	return exp;
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

std::vector<char> Node::toVector(void) const {
    std::vector<char> res;

    res.push_back(getType());

    int length = getLength();

    for(unsigned int i=0; i<4; i++)
    {
	res.push_back(length >> 24);
	length <<= 8;
    }

    for (std::vector<BaseNode *>::const_iterator itr = children.begin(); itr < children.end(); itr++)
    {
	std::vector<char> nextelem = (*itr)->toVector();
	res.insert(res.begin(), nextelem.begin(), nextelem.end());
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

	if(itr < children.end()-1)
	    res += ", ";
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
