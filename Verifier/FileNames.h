#include <string>

typedef const std::string filename;

filename VERSION_FILE = "version";
filename TYPE_FILE = "type";
filename AUXSID_FILE = "auxsid";
filename WIDTH_FILE = "width";

filename FULL_PUBLIC_KEY_FILE	= "FullPublicKey.bt";
filename CIPHERTEXTS_FILE = "Ciphertexts.bt";
filename PLAINTEXTS_FILE = "Plaintexts.bt";
filename SHUFFLED_CIPHERTEXTS_FILE = "ShuffledCiphertexts.bt";

filename PARTIAL_PUBLIC_KEY_FILE_TMPL = "PublicKey%d.bt";
filename PARTIAL_SECRET_KEY_FILE_TMPL = "SecretKey%d.bt";
filename CIPHERTEXTS_FILE_TMPL = "Ciphertexts%d.bt";
filename PERMUTATION_COMMIMENTS_FILE_TMPL = "PermutationCommitment%d.bt";
filename POS_COMMITMENT_FILE_TMPL = "PoSCommitment%d.bt";
filename POS_REPLY_FILE_TMPL = "PoSReply%d.bt";

filename MAXCIPH_FILE = "maxciph";

filename POSC_COMMITMENT_FILE_TMPL = "PoSCCommitment%d.bt";
filename POSC_REPLY_FILE_TMPL = "PoSCReply%d.bt";
filename KEEPLIST_FILE_TMPL = "KeepList%d.bt";
filename CC_POS_COMMITMENT_FILE_TMPL = "CCPoSCommitment%d.bt";
filename CC_POS_REPLY_FILE_TMPL = "CCPoSReply%d.bt";
filename DECRYPTION_FACTORS_FILE_TMPL = "DecryptionFactors%d.bt";
filename DECR_FACT_COMMITMENT_FILE_TMPL = "DecrFactCommitment%d.bt";
filename DECR_FACT_REPLY_FILE_TMPL = "DecrFactReply%d.bt";
