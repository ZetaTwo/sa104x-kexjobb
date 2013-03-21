#ifndef VERIFIER_UTILITIES_H
#define VERIFIER_UTILITIES_H

#include "Node.h"
#include "IntLeaf.h"

struct proofStruct
{
    const IntLeaf *rho;
    int N;
    int nE;
    int nR;
    int nV;
    std::vector<unsigned char> (*hash)(std::vector<unsigned char>);
    const Node *Gq;
    const Node *Rw;
    const Node *Cw;
    const Node *Mw;
    const Node *pk;
    const Node *y;
    const Node *x;
};

bool isElemOf(const Node &group, const IntLeaf &elem);
bool isElemOf(const IntLeaf &Zn, const IntLeaf &elem);
bool isPedersenCommitment(const Node &group, const IntLeaf &elem);

void getGroupFromString(proofStruct &pfStr, std::string str);

const int BOTTOM = 0;

#endif
