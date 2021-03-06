#include <gtest/gtest.h>

#include "H_SHA.h"
#include "PRG.h"

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

TEST(PRGTests, TestVector256) {
	unsigned char data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
								0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
								0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
								0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

	unsigned char expected_data[] = { 0x70, 0xf4, 0x00, 0x3d, 0x52, 0xb6, 0xeb, 0x03, 0xda, 0x85, 0x2e, 0x93, 0x25, 0x6b, 0x59, 0x86,
										0xb5, 0xd4, 0x88, 0x30, 0x98, 0xbb, 0x79, 0x73, 0xbc, 0x53, 0x18, 0xcc, 0x66, 0x63, 0x7a, 0x84,
										0x04, 0xa6, 0x95, 0x0a, 0x06, 0xd3, 0xe3, 0x30, 0x8a, 0xd7, 0xd3, 0x60, 0x6e, 0xf8, 0x10, 0xeb,
										0x12, 0x4e, 0x39, 0x43, 0x40, 0x4c, 0xa7, 0x46, 0xa1, 0x2c, 0x51, 0xc7, 0xbf, 0x77, 0x68, 0x39,
										0x0f, 0x8d, 0x84, 0x2a, 0xc9, 0xcb, 0x62, 0x34, 0x97, 0x79, 0xa7, 0x53, 0x7a, 0x78, 0x32, 0x7d,
										0x54, 0x5a, 0xae, 0xb3, 0x3b, 0x2d, 0x42, 0xc7, 0xd1, 0xdc, 0x36, 0x80, 0xa4, 0xb2, 0x36, 0x28,
										0x62, 0x7e, 0x9d, 0xb8, 0xad, 0x47, 0xbf, 0xe7, 0x6d, 0xbe, 0x65, 0x3d, 0x03, 0xd2, 0xc0, 0xa3,
										0x59, 0x99, 0xed, 0x28, 0xa5, 0x02, 0x39, 0x24, 0x15, 0x0d, 0x72, 0x50, 0x86, 0x68, 0xd2, 0x44 };

	bytevector expected;
	expected.insert(expected.begin(), expected_data, expected_data+128);

	bytevector datavec;
	datavec.insert(datavec.begin(), data, data+32);

	PRG prg(H_SHA256, datavec, 256);
	bytevector result;
	for (int i = 0; i < 128/32; i++)
	{
		bytevector next = prg.next().toVector();
		result.insert(result.end(), next.begin(), next.end());
	}

	EXPECT_EQ(expected, result);
}


TEST(PRGTests, TestVector384) {
	unsigned  char data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
								0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
								0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
								0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
								0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
								0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f };

	unsigned  char expected_data[] = { 0xe4, 0x5a, 0xc6, 0xc0, 0xca, 0xff, 0xf3, 0x43, 0xb2, 0x68, 0xd4, 0xcb, 0xd7, 0x73, 0x32, 0x84,
										0x13, 0x67, 0x2a, 0x76, 0x4d, 0xf9, 0x9a, 0xb8, 0x23, 0xb5, 0x30, 0x74, 0xd9, 0x41, 0x52, 0xbd,
										0x27, 0xfc, 0x38, 0xbc, 0xff, 0xdb, 0x7c, 0x1d, 0xc1, 0xb6, 0xa3, 0x65, 0x6b, 0x2d, 0x48, 0x19,
										0x35, 0x2c, 0x48, 0x2d, 0xa4, 0x0a, 0xad, 0x3b, 0x37, 0xf3, 0x33, 0xc7, 0xaf, 0xa8, 0x1a, 0x92,
										0xb7, 0xb5, 0x45, 0x51, 0xf3, 0x00, 0x9e, 0xfa, 0x4b, 0xdb, 0x89, 0x37, 0x49, 0x2c, 0x5a, 0xfc,
										0xa1, 0xb1, 0x41, 0xc9, 0x91, 0x59, 0xb4, 0xf0, 0xf8, 0x19, 0x97, 0x7a, 0x4e, 0x10, 0xeb, 0x51,
										0x61, 0xed, 0xd4, 0xb1, 0x73, 0x47, 0x17, 0xde, 0x41, 0x06, 0xf9, 0xc1, 0x84, 0xa1, 0x7a, 0x9b,
										0x5e, 0xe6, 0x1a, 0x43, 0x99, 0xdd, 0x75, 0x5f, 0x32, 0x2f, 0x5d, 0x70, 0x7a, 0x58, 0x1c, 0xc1 };

	bytevector expected;
	expected.insert(expected.begin(), expected_data, expected_data+128);

	bytevector datavec;
	datavec.insert(datavec.begin(), data, data+48);

	PRG prg(H_SHA384, datavec, 8*48);
	bytevector result;
	for (int i = 0; i < 3; i++)
	{
		bytevector next = prg.next().toVector();
		result.insert(result.end(), next.begin(), next.end());
	}
	result.resize(128);

	EXPECT_EQ(expected, result);
}

TEST(PRGTests, TestVector512) {
	unsigned char data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
								0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
								0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
								0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f };

	unsigned char expected_data[] = { 0x97, 0x90, 0x43, 0x77, 0x10, 0x43, 0xf4, 0xf8, 0xe0, 0xa2, 0xa1, 0x9b, 0x1f, 0xbf, 0xbe, 0x5a,
										0x8f, 0x07, 0x6c, 0x2b, 0x5a, 0xc0, 0x03, 0xe0, 0xb9, 0x61, 0x9e, 0x0c, 0x45, 0xfa, 0xf7, 0x67,
										0x47, 0x29, 0x57, 0x34, 0x98, 0x06, 0x02, 0xec, 0x1d, 0x8d, 0x3c, 0xd2, 0x49, 0xc1, 0x65, 0xb7,
										0xdb, 0x62, 0xc9, 0x76, 0xcb, 0x90, 0x75, 0xe3, 0x5d, 0x94, 0x19, 0x7c, 0x0f, 0x06, 0xe1, 0xf3,
										0x97, 0xa4, 0x50, 0x17, 0xc5, 0x08, 0x40, 0x1d, 0x37, 0x5a, 0xd0, 0xfa, 0x85, 0x6d, 0xa3, 0xdf,
										0xed, 0x20, 0x84, 0x77, 0x16, 0x75, 0x5c, 0x6b, 0x03, 0x16, 0x3a, 0xec, 0x2d, 0x9f, 0x43, 0xeb,
										0xc2, 0x90, 0x4f, 0x6e, 0x2c, 0xf6, 0x0d, 0x3b, 0x76, 0x37, 0xf6, 0x56, 0x14, 0x5a, 0x2d, 0x32,
										0xa6, 0x02, 0x9f, 0xbd, 0xa9, 0x63, 0x61, 0xe1, 0xb8, 0x09, 0x0c, 0x97, 0x12, 0xa4, 0x89, 0x38 };

	bytevector expected;
	expected.insert(expected.begin(), expected_data, expected_data+128);

	bytevector datavec;
	datavec.insert(datavec.begin(), data, data+64);

	PRG prg(H_SHA512, datavec, 64*8);
	bytevector result;
	for (int i = 0; i < 2; i++)
	{
		bytevector next = prg.next().toVector();
		result.insert(result.end(), next.begin(), next.end());
	}

	EXPECT_EQ(expected, result);
}