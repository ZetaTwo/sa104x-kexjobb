#include <gtest/gtest.h>

#include "BaseNode.h"
#include "Node.h"

#include <stdexcept>

TEST(ByteTreeTests, NodeContructor) {
	Node n;

	EXPECT_EQ(BaseNode::NODE, n.getType());
	EXPECT_EQ(0, n.getLength());
}

TEST(ByteTreeTests, ConcatData) {
	BaseNode *a = new IntLeaf(1234);
	BaseNode *b = new IntLeaf(5678);

	std::vector<unsigned char> result = a->concatData(b);

	char expected_data[] = { 0x04, 0xD2, 0x16, 0x2E };
	std::vector<unsigned char> expected;
	expected.insert(expected.end(), expected_data, expected_data+4);
	EXPECT_EQ(expected, result);
}

TEST(ByteTreeTests, Serialize) {
	char expected_data[] = { 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x02, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x05 };
	std::vector<unsigned char> expected;
	expected.insert(expected.end(), expected_data, expected_data+31);
	
	Node top;
	Node left;
	IntLeaf a(258, 2);
	IntLeaf b(6, 2);
	IntLeaf c(5, 2);

	left.addChild(a);
	left.addChild(b);
	top.addChild(left);
	top.addChild(c);

	std::vector<unsigned char> result = top.serialize();
	
	EXPECT_EQ(expected, result);
}

/*TEST(ByteTreeTests, LeafContructor) {
	Leaf n;

	EXPECT_EQ(BaseNode::LEAF, n.getType());
	EXPECT_EQ(0, n.getLength());
}

TEST(ByteTreeTests, LeafData) {
	const int length = 2;

	Leaf l;
	l.getData().push_back(1);
	l.getData().push_back(2);

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
	
	leaf->getData().push_back(1);
	leaf->getData().push_back(2);

	node.getChildren().push_back(leaf);
	node.getChildren().push_back(leaf);

	EXPECT_EQ(leaf, node[0]);
	EXPECT_EQ(leaf, node[1]);
	EXPECT_THROW(node[2], std::out_of_range);
	EXPECT_THROW(node[-1], std::out_of_range);

	Leaf leaf2 = *static_cast<Leaf*>(node[0]);

	EXPECT_EQ(1, leaf2[0]);
	EXPECT_EQ(2, leaf2[1]);
}*/