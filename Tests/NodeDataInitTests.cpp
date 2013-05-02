#include <gtest/gtest.h>

#include "Node.h"

TEST(NodeDataInitTests, NodeFromFileTest)
{
	std::ifstream file("testfiles/test1.dat", std::ios::in);
	Node node1(file);

	std::string result = node1.toString();

	EXPECT_EQ("((-81, 993), 11602)", result);
}

TEST(NodeDataInitTests, NodeFromFileNameTest)
{
	Node node1("testfiles/test1.dat");

	std::string result = node1.toString();

	EXPECT_EQ("((-81, 993), 11602)", result);
}

TEST(NodeDataInitTests, NodeFromVectorTest)
{
	const unsigned  char arr[] = { 0x00, 0x00, 0x00, 0x00, 0x02, 
									0x00, 0x00, 0x00, 0x00, 0x02,
										0x01, 0x00, 0x00, 0x00, 0x01, 0xAF,
										0x01, 0x00, 0x00, 0x00, 0x02, 0x03, 0xE1, 
									0x01, 0x00, 0x00, 0x00, 0x02, 0x2D, 0x52
						};
	bytevector data(arr, arr + sizeof(arr) / sizeof(arr[0]) );

	Node node1(data);

	std::string result = node1.toString();

	EXPECT_EQ("((-81, 993), 11602)", result);
}