#include <gtest/gtest.h>

#include "BaseNode.h"
#include "Node.h"
#include "Leaf.h"

TEST(ArithmeticTests, PositiveAddition) 
{
    Leaf k(3);
    Leaf l(3);

    k[0] = 0x01;
    k[1] = 0x01;
    k[2] = 0x01;

    l[0] = 0x11;
    l[1] = 0x00;
    l[2] = 0x00;

    k += l;

    EXPECT_EQ(char(0x12), k[0]);
    EXPECT_EQ(char(0x01), k[1]);
    EXPECT_EQ(char(0x01), k[2]);

    Leaf m = k + l;

    EXPECT_EQ(char(0x23), m[0]); 
    EXPECT_EQ(char(0x01), m[1]);
    EXPECT_EQ(char(0x01), m[2]);

    l[2] = 0xA2;

    k += l;

    EXPECT_EQ(char(0x23), k[0]);
    EXPECT_EQ(char(0x01), k[1]);
    EXPECT_EQ(char(0xA3), k[2]);

    Leaf n(32);
    for(unsigned int i=0; i<32; i++)
    {
	n[i] = 0x02;
    }

    Leaf o(9);
    for(unsigned int i=0; i<9; i++)
    {
	o[i] = i;
    }

    m = n + o;

    EXPECT_EQ(char(0x02), m[0]);
    EXPECT_EQ(char(0x07), m[5]);
    EXPECT_EQ(char(0x02), m[31]);

    m = o + n;

    EXPECT_EQ(char(0x02), m[0]);
    EXPECT_EQ(char(0x07), m[5]);
    EXPECT_EQ(char(0x02), m[31]);

}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
