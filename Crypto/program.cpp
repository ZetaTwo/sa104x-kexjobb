#include <iostream>

#include <openssl\sha.h>

int main() {

	unsigned char message[] = "My message";
	unsigned char *hash = new unsigned char[SHA_DIGEST_LENGTH];

	SHA1(message, 10, hash);

	std::cout << message << std::endl;
	for (int i = 0; i < 20; i++) {
        printf("%02x ", hash[i]);
    }

	return 0;
}