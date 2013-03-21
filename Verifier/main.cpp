#include <iostream>
#include <string>
using std::string;

#include "Verifier.h"

int SetMode(const RunMode new_mode, RunMode &mode) {
	if(mode != NONE) {
		std::cerr << "Only one mode of operation can be specified." << std::endl;
		return 1;
	} else {
		mode = new_mode;
		return 0;
	}
}

int ParseProtinfoDirectory(const int i, char * const argv[], string &protInfo, string &directory) {
	protInfo = argv[i+1];
	directory = argv[i+2];

	return 0;
}

int main(int argc, char *argv[]) {
	
	bool verbose = false;
	RunMode mode = NONE;
	string protInfo;
	string directory;

	string auxsid = "default";
	int width = -1;
	bool posc = true;
	bool ccpos = true;
	bool dec = true;

	for (int i = 0; i < argc; i++)
	{
		if(argv[i] == "-v") { //Enable verbose mode
			verbose = true;
		} else if(argv[i] == "-compat") { //Run mode: compat
			if(SetMode(COMPAT, mode)) {
				return 1;
			}
		} else if(argv[i] == "-mix") { //Run mode: mixing
			if(SetMode(MIX, mode)) {
				return 1;
			}

			//Parse extra parameters
			if(i+2 >= argc) {
				std::cerr << "Not enough parameters for -mix" << std::endl;
				return 1;
			}
			ParseProtinfoDirectory(i, argv, protInfo, directory);

		} else if(argv[i] == "-shuffle") {  //Run mode: shuffling
			if(SetMode(SHUFFLE, mode)) {
				return 1;
			}

			//Parse extra parameters
			if(i+2 >= argc) {
				std::cerr << "Not enough parameters for -shuffle" << std::endl;
				return 1;
			}
			ParseProtinfoDirectory(i, argv, protInfo, directory);

		} else if(argv[i] == "-decrypt") {  //Run mode: decryption
			if(SetMode(DECRYPT, mode)) {
				return 1;
			}

			//Parse extra parameters
			if(i+2 >= argc) {
				std::cerr << "Not enough parameters for -decrypt" << std::endl;
				return 1;
			}
			ParseProtinfoDirectory(i, argv, protInfo, directory);

		} else if(argv[i] == "-auxsid") {
			if(i+1 >= argc) {
				std::cerr << "Not enough parameters for -auxsid" << std::endl;
				return 1;
			}
			auxsid = argv[i+1];
		} else if(argv[i] == "-width") {
			if(i+1 >= argc) {
				std::cerr << "Not enough parameters for -width" << std::endl;
				return 1;
			}
			width = atoi(argv[i+1]);
		} else if(argv[i] == "-nopos") {
			posc = false;
			ccpos = false;
		} else if(argv[i] == "-noposc") {
			posc = false;
		} else if(argv[i] == "-noccpos") {
			ccpos = false;
		} else if(argv[i] == "-nodec") {
			dec = false;
		}
	}

	if(mode != NONE && mode != HELP) {
		return Verifier(protInfo, directory, mode, auxsid, width, posc, ccpos, dec);
	}

	return 0;
}
