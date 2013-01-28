#include <gtest/gtest.h>

#include "IntLeaf.h"
#include "Node.h"

TEST(NodeArithmeticTests, VectorAddition)
{
    Node *nodevector1 = new Node();
    Node *nodevector2 = new Node();
    Node nodevector3;

    IntLeaf *leaf = new IntLeaf();
    IntLeaf cmpleaf;

    std::vector<BaseNode *> children = nodevector1->getChildren();

    IntLeaf k;
    for(unsigned int i=0; i<10; i++)
    {
	*leaf = i;
	k = *leaf;
	children.push_back(&k);
    }
    
    children = nodevector2->getChildren();

    for(unsigned int i=0; i<10; i++)
    {
	*leaf = 2*i;
	k = *leaf;
	children.push_back(&k);
    }

    nodevector3 = nodevector1->add(*nodevector2);
    children = nodevector3.getChildren();

    for(unsigned int i=0; i<10; i++)
    {
	cmpleaf = 3*i;
	EXPECT_EQ(((IntLeaf*)children[0])->toString(), cmpleaf.toString());
    }
}


TEST(NodeArithmeticTests, LinkedListNodeAddition)
{
    Node *node1 = new Node();
    Node *node2 = new Node();
    Node node3;
    Node *lastnode;

    lastnode = node1;
    for(unsigned int i=0; i<10; i++)
    {
	std::vector<BaseNode *> children = lastnode->getChildren();
	Node *subnode = new Node();
	IntLeaf *leaf = new IntLeaf(i);

	children.push_back(subnode);
	children.push_back(leaf);
	
	lastnode = subnode;
    }

    lastnode = node2;
    for(unsigned int i=0; i<10; i++)
    {
	std::vector<BaseNode *> children = lastnode->getChildren();
	Node *subnode = new Node();
	IntLeaf *leaf = new IntLeaf(-2*i);

	children.push_back(subnode);
	children.push_back(leaf);
	
	lastnode = subnode;
    }

    node3 = node1->add(*node2);

    lastnode = &node3;
    for(unsigned int i=0; i<10; i++)
    {
	std::vector<BaseNode *> children = lastnode->getChildren();
	IntLeaf *leaf = new IntLeaf(-i);
	
	EXPECT_EQ(((IntLeaf*)children[1])->toString(), leaf->toString());

	lastnode = (Node*) children[0];
    }
}


TEST(NodeArithmeticTests, VectorMultiplication)
{
    Node *nodevector1 = new Node();
    Node *nodevector2 = new Node();
    Node nodevector3;

    IntLeaf *leaf = new IntLeaf();
    IntLeaf cmpleaf;

    std::vector<BaseNode *> children = nodevector1->getChildren();

    IntLeaf k;
    for(unsigned int i=0; i<10; i++)
    {
	*leaf = i;
	k = *leaf;
	children.push_back(&k);
    }
    
    children = nodevector2->getChildren();

    for(unsigned int i=0; i<10; i++)
    {
	*leaf = 2*i;
	k = *leaf;
	children.push_back(&k);
    }

    nodevector3 = nodevector1->mult(*nodevector2);
    children = nodevector3.getChildren();

    for(unsigned int i=0; i<10; i++)
    {
	cmpleaf = 2*i*i;
	EXPECT_EQ(((IntLeaf*)children[0])->toString(), cmpleaf.toString());
    }
}
