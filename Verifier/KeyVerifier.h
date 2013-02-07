#ifndef VERIFIER_KEYVERIFIER_H
#define VERIFIER_KEYVERIFIER_H

#include "Node.h"
#include <string>

/* Arguments:
 *      lambda: number of servers in mix-net
 *      G: underlying group 
 */
Node *verifyKeys(int lambda, const Node &Gq);

bool isPublicKey(Node &node);
bool isPartialPublicKey(IntLeaf &leaf);
bool isPartialSecretKey(IntLeaf &leaf);

const std::string FULL_PUBLIC_KEY_FILE_NAME = "FullPublicKey.bt";
const std::string PARTIAL_PUBLIC_KEY_FILE_PREFIX = "PublicKey";
const std::string PARTIAL_SECRET_KEY_FILE_PREFIX = "SecretKey";

#endif
