#include "H_SHA.h"

#include <algorithm>

#include <openssl\sha.h>

std::vector<unsigned char> H_SHA256(std::vector<unsigned char> seed) {
	return H_SHA(SHA256, seed, SHA256_DIGEST_LENGTH);
}

std::vector<unsigned char> H_SHA384(std::vector<unsigned char> seed) {
	return H_SHA(SHA384, seed, SHA384_DIGEST_LENGTH);
}

std::vector<unsigned char> H_SHA512(std::vector<unsigned char> seed) {
	return H_SHA(SHA512, seed, SHA512_DIGEST_LENGTH);
}

std::vector<unsigned char> H_SHA(unsigned char *(*SHA)(const unsigned char *d, size_t n,unsigned char *md), std::vector<unsigned char> seed, unsigned int digest_length) {
	std::vector<unsigned char> result;
	unsigned char *data = new unsigned char[seed.size()];
	unsigned char *hash = new unsigned char[digest_length];

	std::copy(seed.begin(), seed.end(), data);
	SHA(data, seed.size(), hash);

	result.insert(result.begin(), hash, hash+digest_length);
	delete[] data;
	delete[] hash;

	return result;
}