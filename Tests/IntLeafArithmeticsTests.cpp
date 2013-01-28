#include <gtest/gtest.h>

#include "IntLeaf.h"

TEST(IntLeafArithmeticTests, MultiplicationPositive)
{
    IntLeaf k, l, m;

    k = 641717;
    l = 244436;

    m = k * l;

    EXPECT_EQ("156858736612", m.toString());

    k = 67;
    l = "994851823840149928817400213622";

    m = k * l;

    EXPECT_EQ("66655072197290045230765814312674", m.toString());

    k = 0;
    l = 17;

    m = k * l;

    EXPECT_EQ("0", m.toString());

}

TEST(IntLeafArithmeticTests, AdditionPositive)
{
    IntLeaf k, l, m;

    k = 717146;
    l = 3644931;

    m = k + l;

    EXPECT_EQ("4362077", m.toString());

    k = 19;
    l = 0;

    m = k + l;

    EXPECT_EQ("19", m.toString());

}


TEST(IntLeafArithmeticTests, MultiplicationNegative) 
{
    IntLeaf k, l, m;

    k = -198765;
    l = 12345;

    m = k * l;

    EXPECT_EQ("-2453753925", m.toString());

    k = -15;
    l = -3;

    m = k * l;

    EXPECT_EQ("45", m.toString());
}


TEST(IntLeafArithmeticTests, AdditionNegative)
{
    IntLeaf k, l, m;

    k = 100;
    l = -55;

    m = k + l;

    EXPECT_EQ("45", m.toString());

    k = -13;
    l = -1000000;

    m = k + l;

    EXPECT_EQ("-1000013", m.toString());
}


TEST(IntLeafArithmeticTests, MultiplicationNegative)
{
    IntLeaf k, l, m;

    k = -1;
    l = 23;

    m = k * l;

    EXPECT_EQ("-23", m.toString());

    k = -13;
    l = -12;

    m = k * l;

    EXPECT_EQ("-156", m.toString());
}

