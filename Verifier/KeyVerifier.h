#ifndef VERIFIER_KEYVERIFIER_H
#define VERIFIER_KEYVERIFIER_H

#include "Node.h"
#include "Utilities.h"
#include <string>

bool keyVerifier(int lambda, proofStruct &pfStr);

bool isPublicKey(const Node &G, const Node &pk);
bool isPartialPublicKey(const Node &G, const IntLeaf &ppk);
bool isPartialSecretKey(const Node &G, const IntLeaf &psk);

#endif
