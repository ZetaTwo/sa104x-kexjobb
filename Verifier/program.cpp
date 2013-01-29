#include <fstream>
#include <sstream>
#include <vector>

#include <rapidxml\rapidxml.hpp>

int main() {
	// Read the xml file into a vector
	std::ifstream xml_file("protocol.example.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(xml_file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	
	// Parse the buffer using the xml file parsing library into doc 
	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);
	
	rapidxml::xml_node<> *root_node;
	root_node = doc.first_node("protocol");

	std::string version = root_node->first_node("version")->value();
	std::string sid = root_node->first_node("sid")->value();
	std::string name = root_node->first_node("name")->value();
	std::string descr = root_node->first_node("descr")->value();
	std::string nopart = root_node->first_node("nopart")->value();
	std::string statdist = root_node->first_node("statdist")->value();
	std::string bullboard = root_node->first_node("bullboard")->value();
	std::string thres = root_node->first_node("thres")->value();
	std::string pgroup = root_node->first_node("pgroup")->value();
	std::string cbitlen = root_node->first_node("cbitlen")->value();
	std::string cbitlenro = root_node->first_node("cbitlenro")->value();
	std::string vbitlen = root_node->first_node("vbitlen")->value();
	std::string vbitlenro = root_node->first_node("vbitlenro")->value();
	std::string prg = root_node->first_node("prg")->value();
	std::string rohash = root_node->first_node("rohash")->value();
	std::string corr = root_node->first_node("corr")->value();
	std::string width = root_node->first_node("width")->value();
	std::string maxciph = root_node->first_node("maxciph")->value();

	return 0;
}