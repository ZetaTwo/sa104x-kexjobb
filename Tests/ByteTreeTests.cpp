#include <gtest\gtest.h>

#include "BaseNode.h"
#include "Node.h"
#include "Leaf.h"

TEST(ByteTreeTests, NodeContructor) {
	const int length = 4;

	Node n;

	EXPECT_EQ(BaseNode::NODE, n.getType());
	EXPECT_EQ(length, n.getLength());
}

TEST(ByteTreeTests, LeafContructor) {
	const int length = 4;

	Leaf n;

	EXPECT_EQ(BaseNode::LEAF, n.getType());
	EXPECT_EQ(length, n.getLength());
}

TEST(ByteTreeTests, LeafData) {
	const int length = 2;

	Leaf l;
	l[0] = 1;
	l[1] = 2;

	EXPECT_EQ(1, l[0]);
	EXPECT_EQ(2, l[1]);
	EXPECT_NE(3, l[1]);
	EXPECT_THROW(l[2], std::out_of_range);
	EXPECT_THROW(l[-1], std::out_of_range);
}

TEST(ByteTreeTests, NodeData) {
	const int length = 2;

	Node node;
	Leaf *leaf = new Leaf();
	
	(*leaf)[0] = 1;
	(*leaf)[1] = 2;
	node[0] = leaf;
	node[1] = leaf;

	EXPECT_EQ(leaf, node[0]);
	EXPECT_EQ(leaf, node[1]);
	EXPECT_THROW(node[2], std::out_of_range);
	EXPECT_THROW(node[-1], std::out_of_range);

	Leaf leaf2 = *static_cast<Leaf*>(node[0]);

	EXPECT_EQ(1, leaf2[0]);
	EXPECT_EQ(2, leaf2[1]);
}