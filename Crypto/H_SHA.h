#pragma once

#include <vector>

std::vector<unsigned char> H_SHA(unsigned char *(*SHA)(const unsigned char *d, size_t n,unsigned char *md), std::vector<unsigned char> seed, unsigned int digest_length);

std::vector<unsigned char> H_SHA256(std::vector<unsigned char> seed);
std::vector<unsigned char> H_SHA384(std::vector<unsigned char> seed);
std::vector<unsigned char> H_SHA512(std::vector<unsigned char> seed);