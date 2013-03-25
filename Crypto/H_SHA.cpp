#include "H_SHA.h"

#include <algorithm>

#include <openssl/sha.h>

bytevector H_SHA256(bytevector seed) {
	return H_SHA(SHA256, seed, SHA256_DIGEST_LENGTH);
}

bytevector H_SHA384(bytevector seed) {
	return H_SHA(SHA384, seed, SHA384_DIGEST_LENGTH);
}

bytevector H_SHA512(bytevector seed) {
	return H_SHA(SHA512, seed, SHA512_DIGEST_LENGTH);
}

bytevector H_SHA(unsigned char *(*SHA)(const unsigned char *d, size_t n,unsigned char *md), bytevector seed, unsigned int digest_length) {
	bytevector result;
	unsigned char *data = new unsigned char[seed.size()];
	unsigned char *hash = new unsigned char[digest_length];

	std::copy(seed.begin(), seed.end(), data);
	SHA(data, seed.size(), hash);

	result.insert(result.begin(), hash, hash+digest_length);
	delete[] data;
	delete[] hash;

	return result;
}
