#ifndef VERIFIER_KEYVERIFIER_H
#define VERIFIER_KEYVERIFIER_H

#include "Node.h"
#include <string>

/* keyVerifier:
 *      lambda: number of servers in mix-net
 *      G: underlying group 
 *      key_node: empty node that on return will be filled with (pk, pub_keys, sec_keys)
 */
bool keyVerifier(int lambda, const Node &G, Node &key_node);

bool isPublicKey(Node &node);
bool isPartialPublicKey(IntLeaf &leaf);
bool isPartialSecretKey(IntLeaf &leaf);

const std::string FULL_PUBLIC_KEY_FILE_NAME = "FullPublicKey.bt";
const std::string PARTIAL_PUBLIC_KEY_FILE_PREFIX = "PublicKey";
const std::string PARTIAL_SECRET_KEY_FILE_PREFIX = "SecretKey";

#endif
