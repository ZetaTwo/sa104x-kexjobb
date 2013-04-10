#ifndef VERIFIER_FILENAMES_H
#define VERIFIER_FILENAMES_H

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

filename PARTIAL_PUBLIC_KEY_FILE_TMPL = "PublicKey%02d.bt";
filename PARTIAL_SECRET_KEY_FILE_TMPL = "SecretKey%02d.bt";
filename CIPHERTEXTS_FILE_TMPL = "Ciphertexts%02d.bt";
filename PERMUTATION_COMMIMENTS_FILE_TMPL = "PermutationCommitment%02d.bt";
filename POS_COMMITMENT_FILE_TMPL = "PoSCommitment%02d.bt";
filename POS_REPLY_FILE_TMPL = "PoSReply%02d.bt";

filename MAXCIPH_FILE = "maxciph";

filename POSC_COMMITMENT_FILE_TMPL = "PoSCCommitment%02d.bt";
filename POSC_REPLY_FILE_TMPL = "PoSCReply%02d.bt";
filename KEEPLIST_FILE_TMPL = "KeepList%02d.bt";
filename CC_POS_COMMITMENT_FILE_TMPL = "CCPoSCommitment%02d.bt";
filename CC_POS_REPLY_FILE_TMPL = "CCPoSReply%02d.bt";
filename DECRYPTION_FACTORS_FILE_TMPL = "DecryptionFactors%02d.bt";
filename DECR_FACT_COMMITMENT_FILE_TMPL = "DecrFactCommitment%02d.bt";
filename DECR_FACT_REPLY_FILE_TMPL = "DecrFactReply%02d.bt";

const unsigned int FILENAME_BUFFER_SIZE = 100;

#endif
