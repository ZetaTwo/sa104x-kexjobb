#ifndef VERIFIER_VERIFIER_H
#define VERIFIER_VERIFIER_H

#include <string>
using std::string;

enum RunMode { NONE, HELP, COMPAT, MIX, SHUFFLE, DECRYPT };

int Verifier(string protinfo, string directory,
				 RunMode typeExp, string auxsidExp, int wExp,
				 bool posc, bool ccpos, bool dec);


#endif
