#include "RandomArray.h"

Node RandomArray(Node Gq, unsigned int Nprime, PRG &prg, unsigned int Nr) {

	prg.next();
	unsigned int Nq = Gq.getChild(0).getLength() * 8;

}