#include <gtest/gtest.h>

#include "IntLeaf.h"
#include "Node.h"

TEST(NodeSerializeTests, SerializeString)
{
	Node node, pair;
    
    pair.addChild(IntLeaf(1));
    pair.addChild(IntLeaf(2));

    node.addChild(pair);
    node.addChild(IntLeaf(3));

	std::string a = node.serializeString();

	EXPECT_EQ("00000000020000000002010000000101010000000102010000000103", a);
}