#ifndef VERIFIER_PROOFOFSHUFFLE_H
#define VERIFIER_PROOFOFSHUFFLE_H

#include "Node.h"
#include "Utilities.h"

bool proofOfShuffle(proofStruct &pfStr, 
		    const Node &w, 
		    const Node &w_prime, 
		    const Node &mu,
		    const Node &tau_pos, 
		    const Node &sigma_pos);

#endif


