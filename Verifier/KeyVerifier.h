#include "Node.h"
#include <string>

/* Arguments:
 *      nr_servers: number of servers in mix-net
 *      G: underlying group 
 */
Node *verifyKeys(int nr_servers, Node &G);

bool isPublicKey(Node &node);
bool isPartialPublicKey(IntLeaf &leaf);
bool isPartialSecretKey(IntLeaf &leaf);

const std::string FULL_PUBLIC_KEY_FILE_NAME = "FullPublicKey.bt";
const std::string PARTIAL_PUBLIC_KEY_FILE_PREFIX = "PublicKey";
const std::string PARTIAL_SECRET_KEY_FILE_PREFIX = "SecretKey";
