#pragma once

#include <vector>
#include "types.h"

bytevector H_SHA(unsigned char *(*SHA)(const unsigned char *d, size_t n,unsigned char *md), bytevector seed, unsigned int digest_length);

bytevector H_SHA256(bytevector seed);
bytevector H_SHA384(bytevector seed);
bytevector H_SHA512(bytevector seed);