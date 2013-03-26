#include <gtest/gtest.h>

#include "IntLeaf.h"
#include "Node.h"

TEST(NodeArithmeticsTests, AddChildren)
{
	Node nodevector;
    for(unsigned int i=0; i<10; i++)
    {
		nodevector.addChild(IntLeaf(i));
    }
   
	std::string result_string = nodevector.toString();

    EXPECT_EQ("(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)", result_string);
}

TEST(NodeArithmeticsTests, VectorAddition)
{
    Node nodevector;
    Node result;

    Node expected;

    for(unsigned int i=0; i<10; i++)
    {
	nodevector.addChild(IntLeaf(i));
	expected.addChild(IntLeaf(3 + i));	     
    }
    
    result = nodevector.add(IntLeaf(3));

    EXPECT_EQ(expected, result);
}


TEST(NodeArithmeticsTests, LinkedListNodeAddition)
{
    
}


TEST(NodeArithmeticsTests, VectorMultiplication)
{
    Node *nodevector = new Node();
    Node result;
    Node expected;

    for(unsigned int i=0; i<10; i++)
    {
	nodevector->addChild(IntLeaf(i));
	expected.addChild(IntLeaf(3*i));
    }
    
    result = nodevector->mult(IntLeaf(3));

    EXPECT_EQ(expected, result);
}

