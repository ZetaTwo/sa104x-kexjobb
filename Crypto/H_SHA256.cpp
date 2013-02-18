#include "H_SHA256.h"

#include <algorithm>

#include <openssl\sha.h>

std::vector<unsigned char> H_SHA256(std::vector<unsigned char> seed) {
	std::vector<unsigned char> result;
	unsigned char *data = new unsigned char[seed.size()];
	unsigned char *hash = new unsigned char[seed.size()];

	std::copy(seed.begin(), seed.end(), data);
	SHA256(data, seed.size(), hash);

	std::copy(hash, hash+seed.size(), result.begin());
	delete[] data;
	delete[] hash;

	return result;
}