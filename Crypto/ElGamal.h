#include "Node.h"
#include "IntLeaf.h"

IntLeaf PDec(IntLeaf x, IntLeaf c, IntLeaf mod);
IntLeaf TDec(IntLeaf x, IntLeaf c, IntLeaf mod);
Node Enc(Node pk, IntLeaf m, IntLeaf s, IntLeaf mod);
