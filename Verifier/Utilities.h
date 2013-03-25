#ifndef VERIFIER_UTILITIES_H
#define VERIFIER_UTILITIES_H

#include <string>

#include "Node.h"
#include "IntLeaf.h"

struct proofStruct
{
    IntLeaf rho;
    unsigned int N;
    unsigned int lambda;
    unsigned int width;
    unsigned int nE;
    unsigned int nR;
    unsigned int nV;
    unsigned int nHash;
    bytevector (*hash)(bytevector);
    Node Gq;
    Node Rw;
    Node pk;
    Node y;
    Node x;
};

bool isElemOfGq(const Node &group, const IntLeaf &elem);
bool isElemOfZn(const IntLeaf &n, const IntLeaf &elem);
bool isElemOfCw(const proofStruct &pfStr, const Node &ciphertext);
bool isElemOfMw(const proofStruct &pfStr, const Node &plaintext);

// Todo: Replace with above functions
bool isElemOf(const Node &group, const IntLeaf &elem);
bool isElemOf(const IntLeaf &Zn, const IntLeaf &elem);


bool isPedersenCommitment(const Node &group, const IntLeaf &elem);

void getGroupFromString(proofStruct &pfStr, std::string str);

const int BOTTOM = 0;

#endif
