#include <gtest/gtest.h>

#include "H_SHA256.h"
#include "PRG.h"

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

TEST(PRGTests, TestVector1) {
	char *data = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
	std::vector<unsigned char> datavec;
	datavec.insert(datavec.begin(), data, data+32);

	PRG prg(H_SHA256, datavec);
	std::cout << prg.next().toString() << std::endl;
	EXPECT_EQ(1, 0);
}