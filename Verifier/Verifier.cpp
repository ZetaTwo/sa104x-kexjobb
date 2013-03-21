#include "Verifier.h"
#include "Utilities.h"
#include "DecryptionVerifier.h"
#include "ShufflingVerifier.h"
#include "KeyVerifier.h"
#include "FileNames.h"

#include <string>
#include <fstream>
#include <vector>

using std::string;

#include <rapidxml/rapidxml.hpp>

#include "DataLeaf.h"
#include "Node.h"
#include "H_SHA.h"

int Verifier(string protinfo, string directory,
				 RunMode typeExp, string auxsidExp, int wExp,
				 bool posc, bool ccpos, bool dec) {
    
    proofStruct pfStr;

    //Step 1
    // Read the xml file into a vector
    std::ifstream xml_file(protinfo);
    std::vector<char> buffer((std::istreambuf_iterator<char>(xml_file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    
    // Parse the buffer using the xml file parsing library into doc 
    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);
    
    rapidxml::xml_node<> *root_node;
    root_node = doc.first_node("protocol");

    string versionProt;
    string Sh;
    string sid;
    string pGroup;
    IntLeaf Nv;
    IntLeaf Ne;

    int lambda;
    
    try {
	versionProt = root_node->first_node("version")->value();
	sid = root_node->first_node("sid")->value();
	string k = root_node->first_node("nopart")->value();
	
	string strLambda = root_node->first_node("thres")->value();
	lambda = atol(strLambda.c_str());
	
	pGroup = root_node->first_node("pgroup")->value();
	getGroupFromString(pfStr, pGroup);

	string strNv = root_node->first_node("cbitlen")->value();
	Nv = atol(strNv.c_str());
	
	string strNe = root_node->first_node("vbitlen")->value();
	Ne = atol(strNe.c_str());
	
	string Sprg = root_node->first_node("prg")->value();
	Sh = root_node->first_node("rohash")->value();
	string Cw = root_node->first_node("width")->value();
    } catch (...) {
	return false;
    }
    
    xml_file.close();
    
    //Step 2
    string versionProof;
    string typeStr;
	RunMode type;
    string auxsid;
	int width;
    string widthStr;
    
    std::ifstream datafile(directory + "/version", std::ios::in);
    datafile >> versionProof;
    if(versionProof != versionProt) { return false; }
    
    datafile.open(directory + "/type");
    datafile >> typeStr;
	if(typeStr == "mixing") { type = MIX; }
	if(typeStr == "shuffling") { type = SHUFFLE; }
	if(typeStr == "decryption") { type = DECRYPT; }

    if(type != typeExp) { return false; }
    
    datafile.open(directory + "/auxsid");
    datafile >> auxsid;
    if(auxsid != auxsidExp) { return false; }
    
    datafile.open(directory + "/width");
    datafile >> widthStr;
	width = atoi(widthStr.c_str());
    if(wExp != -1 && wExp != width) { return false; }
    
    //Step 3
	if(Sh == "SHA-256") {
		pfStr.hash = H_SHA256;
	} else if(Sh == "SHA-384") {
		pfStr.hash = H_SHA384;
	} else if(Sh == "SHA-512") {
		pfStr.hash = H_SHA512;
	} else {
		return false;
	}
    
    //Step 4
    //rho = H(node(versionProof, sid + "." auxsid, omega, Ne, Nr, Nv, Gq, Sprg, Sh))
	DataLeaf rho_version;
	std::vector<unsigned char> version_data = rho_version.getData();
	version_data.insert(version_data.end(), versionProof.begin(), versionProof.end());

	DataLeaf rho_id;
	std::vector<unsigned char> id_data = rho_id.getData();
	id_data.insert(id_data.end(), sid.begin(), sid.end());
	id_data.push_back('.');
	id_data.insert(id_data.begin(), auxsid.begin(), auxsid.end());
	
	Node rho;
	rho.addChild(rho_version);
	rho.addChild(rho_id);
	rho.addChild(IntLeaf(width));
	rho.addChild(Ne);
	rho.addChild(...);
	rho.addChild(Nv);

    
    //Step 5
	
    Node key_node;
    
    if(!keyVerifier(lambda, pfStr))
    {
	return false;
    }
    

    //Step 6 Read lists
        
    Node L0;
    Node Llambda;

    /* Read first ciphertext */
    try {
		const std::string ciphertext_file_name = CIPHERTEXT_FILE_PREFIX + std::to_string(0) + FILE_SUFFIX;
		std::ifstream fstr(ciphertext_file_name, std::fstream::in);

	L0 = Node(fstr);
    }
    catch(...)
    {
	return 0;
    }
    
    pfStr.N = L0.getLength();

    if(type == MIX) {
	/* Read threshold ciphertext */
		try {
			const std::string ciphertext_file_name = CIPHERTEXT_FILE_PREFIX + std::to_string(lambda) + FILE_SUFFIX;
			std::ifstream fstr(ciphertext_file_name, std::fstream::in);
	    
	    Llambda = Node(fstr);
	}
	catch(...)
	{
	    return 0;
	}
    }
	else if(type == SHUFFLE)
    {
	/* Read threshold ciphertext */
	try
	{
	    std::ifstream fstr(SHUFFLED_CIPHERTEXTS_FILE, std::fstream::in);
	    
	    Llambda = Node(fstr);
	}
	catch(...)
	{
	    return 0;
	}
    }

    Node m;
	if(type == MIX || type == DECRYPT)
    {
		/* Read plaintexts */
		try {
			std::ifstream fstr(PLAINTEXTS_FILE, std::fstream::in); 
			m = Node(fstr);
		} catch(...) {
			return 0;
		}
    }
	
    //Step 7 Verify relations between lists

	if((type == MIX || type == SHUFFLE) &&
       (posc || ccpos))
    {
	if(!verifyShuffling(pfStr, lambda, L0, Llambda, posc, ccpos))
	{
	    return false;
	}
		
    }
    
    if(dec && type == MIX)
    {
	Node L = Llambda;
	if(!DecryptionVerifier(pfStr, L, m))
	{
	    return false;
	}
    }
	else if(dec && type == DECRYPT)
    {
	Node L = L0;
	if(!DecryptionVerifier(pfStr, L, m))
	{
	    return false;
	}    }

    return false;
}
