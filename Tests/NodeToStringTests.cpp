#include <gtest/gtest.h>

#include "IntLeaf.h"
#include "Node.h"

TEST(NodeToStringTests, Vector)
{
    Node nodevector;

    for(unsigned int i=0; i<10; i++)
    {
		IntLeaf leaf(i);
		nodevector.addChild(leaf);
    }

    EXPECT_EQ(nodevector.toString(), "(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)");
}


TEST(NodeToStringTests, PairVector)
{
    Node node;

    for(unsigned int i=0; i<7; i++)
    {
		Node pair;
		pair.addChild(IntLeaf(i));
		pair.addChild(IntLeaf(10+i));

		node.addChild(pair);
    }

    EXPECT_EQ(node.toString(), "((0, 10), (1, 11), (2, 12), (3, 13), (4, 14), (5, 15), (6, 16))");
}


TEST(NodeToStringTests, PairSingle)
{
    Node node;
    
    Node pair;
    pair.addChild(IntLeaf(1));
    pair.addChild(IntLeaf(2));

    node.addChild(pair);
    node.addChild(IntLeaf(3));

    EXPECT_EQ(node.toString(), "((1, 2), 3)");
}



