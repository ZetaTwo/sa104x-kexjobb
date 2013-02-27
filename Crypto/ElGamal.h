#include "Node.h"
#include "IntLeaf.h"

IntLeaf PDec(IntLeaf x, Node c, IntLeaf mod);
IntLeaf TDec(Node x, Node c, IntLeaf mod);
Node Enc(Node pk, IntLeaf m, IntLeaf s, IntLeaf mod);
