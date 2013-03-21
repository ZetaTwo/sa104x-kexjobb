#include <string>
using std::string;

enum RunMode { NONE, HELP, COMPAT, MIX, SHUFFLE, DECRYPT };

int Verifier(string protinfo, string directory,
				 RunMode typeExp, string auxsidExp, int wExp,
				 bool posc, bool ccpos, bool dec);


const std::string CIPHERTEXT_FILE_PREFIX = "Ciphertexts";

