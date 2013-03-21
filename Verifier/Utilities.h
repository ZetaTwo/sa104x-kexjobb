#ifndef VERIFIER_UTILITIES_H
#define VERIFIER_UTILITIES_H

#include <string>

#include "Node.h"
#include "IntLeaf.h"

struct proofStruct
{
    IntLeaf rho;
    unsigned int N;
    unsigned int nE;
    unsigned int nR;
    unsigned int nV;
    unsigned int nHash;
    std::vector<unsigned char> (*hash)(std::vector<unsigned char>);
    Node Gq;
    Node Rw;
    Node Cw;
    Node Mw;
    Node pk;
    Node y;
    Node x;
};

bool isElemOf(const Node &group, const IntLeaf &elem);
bool isElemOf(const IntLeaf &Zn, const IntLeaf &elem);
bool isPedersenCommitment(const Node &group, const IntLeaf &elem);

void getGroupFromString(proofStruct &pfStr, std::string str);

const int BOTTOM = 0;

#endif
