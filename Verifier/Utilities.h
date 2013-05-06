#ifndef VERIFIER_UTILITIES_H
#define VERIFIER_UTILITIES_H

#include <string>

#include "Node.h"
#include "IntLeaf.h"

struct proofStruct
{
    std::string directory;
	bytevector rho;
    unsigned int k;
    unsigned int N;
    unsigned int lambda;
    unsigned int width;
    unsigned int nE;
    unsigned int nR;
    unsigned int nV;
    unsigned int nH;
    bytevector (*hash)(bytevector);
    Node Gq;
    Node Rw;
    Node pk;
    Node y;
    Node x;
};

bool isElemOfGq(const Node &group, const IntLeaf &elem);
bool isElemOfZn(const IntLeaf &n, const IntLeaf &elem);
bool isElemOfCw(const proofStruct &pfStr, const Node &uv);
bool isElemOfMw(const proofStruct &pfStr, const Node &plaintext);
bool isElemOfRw(const proofStruct &pfStr, const Node &random);

bool isPedersenCommitment(const Node &group, const IntLeaf &elem);

void getGroupFromString(proofStruct &pfStr, std::string str);

const IntLeaf BOTTOM = IntLeaf(-1);

#endif
