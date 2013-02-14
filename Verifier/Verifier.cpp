#include "Verifier.h"

#include <string>
#include <fstream>
#include <vector>

using std::string;

#include <rapidxml\rapidxml.hpp>

#include "PRG.h"

bool Verifier(string protinfo, string directory,
				 string typeExp, string auxsidExp, string wExp,
				 bool posc, bool ccpos, bool dec) {
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

	try {
		versionProt = root_node->first_node("version")->value();
		string sid = root_node->first_node("sid")->value();
		string k = root_node->first_node("nopart")->value();
		string lambda = root_node->first_node("thres")->value();
		string Nv = root_node->first_node("cbitlen")->value();
		string Ne = root_node->first_node("vbitlen")->value();
		string Sprg = root_node->first_node("prg")->value();
		Sh = root_node->first_node("rohash")->value();
		string Cw = root_node->first_node("width")->value();
	} catch (...) {
		return false;
	}

	xml_file.close();

	//Step 2
	string versionProof;
	string type;
	string auxsid;
	string width;

	std::ifstream datafile(directory + "/version", std::ios::in);
	datafile >> versionProof;
	if(versionProof != versionProt) { return false; }

	datafile.open(directory + "/type");
	datafile >> type;
	if(type != typeExp) { return false; }

	datafile.open(directory + "/auxsid");
	datafile >> auxsid;
	if(auxsid != auxsidExp) { return false; }

	datafile.open(directory + "/width");
	datafile >> width;
	if(wExp != "" && wExp != width) { return false; }

	//Step 3
	//H *h = switch(...);

	PRG *prg;
	if(Sh == "SHA-256") {
		prg = new SHA256_PRG();
	} else {
		return false;
	}

	//Step 4
	//rho = H(node(versionProof, sid + "." auxsid, omega, Ne, Nr, Nv, Gq, Sprg, Sh))

	//Step 5
	//keys = Algorithm23(...)

	//Step 6


	//Step 7

	return false;
}