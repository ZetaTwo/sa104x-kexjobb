#include <gtest/gtest.h>

#include "IntLeaf.h"
#include "Node.h"

TEST(NodeArithmeticsTests, VectorAddition)
{
    Node *nodevector1 = new Node();
    Node *nodevector2 = new Node();
    Node result;

    IntLeaf *leaf = new IntLeaf();
    IntLeaf cmpleaf;

    for(unsigned int i=0; i<10; i++)
    {
	nodevector1->addChild(IntLeaf(i));
	nodevector2->addChild(IntLeaf(2*i));
    }
    
    result = nodevector1->add(IntLeaf(1));


    EXPECT_EQ("(0, 3, 6, 9, 12, 15, 18, 21, 24, 27)", result.toString());
}


TEST(NodeArithmeticsTests, LinkedListNodeAddition)
{
    
}


TEST(NodeArithmeticTests, VectorMultiplication)
{
    Node *nodevector1 = new Node();
    Node *nodevector2 = new Node();
    Node result;

    IntLeaf *leaf = new IntLeaf();
    IntLeaf cmpleaf;

    for(unsigned int i=0; i<10; i++)
    {
	nodevector1->addChild(IntLeaf(i));
	nodevector2->addChild(IntLeaf(2*i));
    }
    
    result = nodevector1->mult(IntLeaf(1));


    EXPECT_EQ("(0, 3, 6, 9, 12, 15, 18, 21, 24, 27)", result.toString());
}

