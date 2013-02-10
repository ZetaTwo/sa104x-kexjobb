#include <iostream>
#include <string>

#include <openssl/sha.h>

int main() {

	std::string message = "My message";
	unsigned char *hash = new unsigned char[SHA256_DIGEST_LENGTH];

	SHA256((unsigned char*)message.c_str(), message.length(), hash);

	std::cout << message << std::endl;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x ", hash[i]);
    }

	return 0;
}