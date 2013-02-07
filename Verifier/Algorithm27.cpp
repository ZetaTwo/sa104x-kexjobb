#include "Algorithm27.h"

#include <string>
#include <fstream>
#include <vector>

using std::string;

#include <rapidxml\rapidxml.hpp>


bool Algorithm27(string protinfo, string directory,
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

	try {
		string versionProt = root_node->first_node("version")->value();
		string sid = root_node->first_node("sid")->value();
		//string name = root_node->first_node("name")->value();
		//string descr = root_node->first_node("descr")->value();
		string k = root_node->first_node("nopart")->value();
		//string statdist = root_node->first_node("statdist")->value();
		//string bullboard = root_node->first_node("bullboard")->value();
		string lambda = root_node->first_node("thres")->value();
		string pgroup = root_node->first_node("pgroup")->value();
		string cbitlen = root_node->first_node("cbitlen")->value();
		string cbitlenro = root_node->first_node("cbitlenro")->value();
		string vbitlen = root_node->first_node("vbitlen")->value();
		string vbitlenro = root_node->first_node("vbitlenro")->value();
		string prg = root_node->first_node("prg")->value();
		string rohash = root_node->first_node("rohash")->value();
		string corr = root_node->first_node("corr")->value();
		string width = root_node->first_node("width")->value();
		string maxciph = root_node->first_node("maxciph")->value();
	} catch (...) {
		return false;
	}


	return false;
}