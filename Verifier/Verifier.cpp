#include "Debug.h"

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
    pfStr.directory = directory;

    //Step 1
    // Read the xml file into a vector
    std::ifstream xml_file(protinfo.c_str());
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
    string Sprg;
    unsigned int wDefault;

    // Set values in proofStruct
    try {
        versionProt = root_node->first_node("version")->value();
        sid = root_node->first_node("sid")->value();
        string k = root_node->first_node("nopart")->value();
        pfStr.k = atol(k.c_str());

        string strLambda = root_node->first_node("thres")->value();
        pfStr.lambda = atol(strLambda.c_str());

        pGroup = root_node->first_node("pgroup")->value();
        getGroupFromString(pfStr, pGroup);

        string strNv = root_node->first_node("cbitlenro")->value();
        pfStr.nV = atol(strNv.c_str());

        string strNe = root_node->first_node("vbitlenro")->value();
        pfStr.nE = atol(strNe.c_str());

        string strNr = root_node->first_node("statdist")->value();
		pfStr.nR = atol(strNr.c_str());

        Sprg = root_node->first_node("prg")->value();
        Sh = root_node->first_node("rohash")->value();
        string strwidth = root_node->first_node("width")->value();
        wDefault = atol(strwidth.c_str());

    } catch (...) {
	print_debug("Verifier: could not parse", protinfo);
	return false;
    }

    xml_file.close();

    //Step 2
    string versionProof;
    string typeStr;
    RunMode type;
    string auxsid;
    string widthStr;

    string filename = pfStr.directory + "/version";
    std::ifstream datafile(filename.c_str(), std::ios::in);
    datafile >> versionProof;
    datafile.close();
    
    if(versionProof != versionProt) { return false; }

    //Determine type
    filename = pfStr.directory + "/type";
    datafile.open(filename.c_str());
    datafile >> typeStr;
    datafile.close();
    if(typeStr == "mixing") { type = MIX; }
    if(typeStr == "shuffling") { type = SHUFFLE; }
    if(typeStr == "decryption") { type = DECRYPT; }

    // Make sure that type is the expected type
    if(type != typeExp) { return false; }

    // Check auxid
    filename = pfStr.directory + "/auxsid";
    datafile.open(filename.c_str());
    datafile >> auxsid;
    datafile.close();
    if(auxsid != auxsidExp) { return false; }

    // Check width parameters
    filename = pfStr.directory + "/width";
    datafile.open(filename.c_str());
    datafile >> widthStr;
    datafile.close();
    pfStr.width = atoi(widthStr.c_str());
    if(wExp != -1 && wExp != pfStr.width) { return false; }
    if(wExp == -1 && wDefault != pfStr.width) { return false; }

    //Step 3
    if(Sh == "SHA-256") {
        pfStr.hash = H_SHA256;
        pfStr.nH = 256;
    } else if(Sh == "SHA-384") {
        pfStr.hash = H_SHA384;
        pfStr.nH = 384;
    } else if(Sh == "SHA-512") {
        pfStr.hash = H_SHA512;
        pfStr.nH = 512;
    } else {
        return false;
    }

    //Step 4
    //rho = H(node(versionProof, sid + "." auxsid, w, Ne, Nr, Nv, SGq, Sprg, Sh))
    Node rho;
    rho.addChild((DataLeaf)versionProof);
    rho.addChild((DataLeaf)(sid + "." + auxsid));
    rho.addChild(IntLeaf(pfStr.width,  4));
    rho.addChild(IntLeaf(pfStr.nE, 4));
    rho.addChild(IntLeaf(pfStr.nR, 4));
    rho.addChild(IntLeaf(pfStr.nV, 4));
    rho.addChild((DataLeaf)pGroup);
    rho.addChild((DataLeaf)Sprg);
    rho.addChild((DataLeaf)Sh);

    print_debug("Verifier: rho hash input", rho.serializeString());
    
    pfStr.rho = pfStr.hash(rho.serialize());

    print_debug("Verifier: rho", pfStr.rho);
    
    //Step 5
    if(!keyVerifier(pfStr))
    {
        return false;
    }

    print_debug("Verifier: p", pfStr.Gq.getIntLeafChild(0).serializeString());
    print_debug("Verifier: pk", pfStr.pk.serializeString());
    print_debug("Verifier: y", pfStr.y.serializeString());
    print_debug("Verifier: x", pfStr.x.serializeString());

    //Step 6 Read lists
    Node L0;
    Node Llambda;

    /* Read first ciphertext */
    try {
        std::ifstream fstr((pfStr.directory + "/" + CIPHERTEXTS_FILE).c_str(), std::fstream::in | std::fstream::binary);
        L0 = Node(fstr);
    }
    catch(...) {
        return false;
    }

    // Define N
    if(pfStr.width == 1) {
        pfStr.N = L0.getNodeChild(0).getLength();
    } else {
        pfStr.N = L0.getNodeChild(0).getNodeChild(0).getLength();
    }

    print_debug("Verifier: L0", L0.serializeString());
    print_debug("Verifier: N", pfStr.N);

    if(type == MIX) {
        /* Read threshold ciphertext */
        try {

            char ciphertext_filename[FILENAME_BUFFER_SIZE];
            sprintf(ciphertext_filename, CIPHERTEXTS_FILE_TMPL.c_str(), pfStr.lambda);

            std::ifstream fstr((pfStr.directory + "/proofs/" + ciphertext_filename).c_str(), std::fstream::in | std::fstream::binary);
            Llambda = Node(fstr);
        }
        catch(...) {
            return 0;
        }
    }
    else if(type == SHUFFLE) {
        /* Read threshold ciphertext */
        try {
            std::ifstream fstr(SHUFFLED_CIPHERTEXTS_FILE.c_str(), std::fstream::in);

            Llambda = Node(fstr);
        }
        catch(...) {
            return 0;
        }
    }

    Node m;
    if(type == MIX || type == DECRYPT)
    {
        /* Read plaintexts */
        try {
            std::ifstream fstr((pfStr.directory + "/" + PLAINTEXTS_FILE.c_str()).c_str(), std::fstream::in | std::fstream::binary); 
            m = Node(fstr);
        } catch(...) {
            return 0;
        }
    }

    //Step 7 Verify relations between lists

    //TODO: s blir fel här inne
    if((type == MIX || type == SHUFFLE) &&
        (posc || ccpos))
    {
        if(!verifyShuffling(pfStr, L0, Llambda, posc, ccpos))
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
        }
    }

    return true;
}
