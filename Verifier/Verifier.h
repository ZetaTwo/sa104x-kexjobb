#include <string>

using std::string;

bool Verifier(string protinfo, string directory,
				 string typeExp, string auxsidExp, string wExp,
				 bool posc, bool ccpos, bool dec);


const std::string CIPHERTEXT_FILE_PREFIX = "Ciphertexts";
