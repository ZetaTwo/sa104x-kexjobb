#ifndef VERIFIER_SHUFFLINGVERIFIER_H
#define VERIFIER_SHUFFLINGVERIFIER_H

#include <string>

#include "Node.h"
#include "Utilities.h"

bool verifyShuffling(proofStruct &pfStr,
		     int lambda,
		     Node &L0,
		     Node &Llambda,
		     bool posc, 
		     bool ccpos);

bool isListOfCiphertexts(const proofStruct &pfStr, Node &L);

//const std::string CIPHER_TEXTS_FILE_NAME_PREFIX = "CipherText";

#endif



