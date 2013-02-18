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

    for(unsigned int i=0; i<10; i++)
    {
		nodevector.addChild(IntLeaf(i));
    }
    
	result = nodevector.add(IntLeaf(3));

    EXPECT_EQ("(3, 4, 5, 6, 7, 8, 9, 10, 11, 12)", result.toString());
}


TEST(NodeArithmeticsTests, LinkedListNodeAddition)
{
    
}


TEST(NodeArithmeticsTests, VectorMultiplication)
{
    Node *nodevector = new Node();
    Node result;

    for(unsigned int i=0; i<10; i++)
    {
		nodevector->addChild(IntLeaf(i));
    }
    
    result = nodevector->mult(IntLeaf(3));

    EXPECT_EQ("(0, 3, 6, 9, 12, 15, 18, 21, 24, 27)", result.toString());
}

