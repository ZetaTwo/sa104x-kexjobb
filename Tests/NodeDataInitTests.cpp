#include <gtest/gtest.h>

#include "Node.h"

TEST(NodeDataInitTests, NodeFromFileTest)
{
	std::ifstream file("testfiles/test1.txt", std::ios::in);
	Node node1(file);

	std::string result = node1.toString();

	EXPECT_EQ("((-81, 993), 11602)", result);
}

TEST(NodeDataInitTests, NodeFromFileNameTest)
{
	Node node1("testfiles/test1.txt");

	std::string result = node1.toString();

	EXPECT_EQ("((-81, 993), 11602)", result);
}

TEST(NodeDataInitTests, NodeFromVectorTest)
{
	const char arr[] = "000000000200000000020100000001AF010000000203E101000000022D52";
	std::vector<char> data(arr, arr + sizeof(arr) / sizeof(arr[0]) );

	Node node1(data);

	std::string result = node1.toString();

	EXPECT_EQ("((-81, 993), 11602)", result);
}