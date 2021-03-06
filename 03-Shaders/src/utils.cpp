#include "utils.hpp"

void utls::readFile(std::string path, std::string & readBuf) {
	std::ifstream f(path, std::ios::ate);
	if(f.is_open()) {
		auto size = f.tellg();
		f.seekg(0);
		std::string str(size, '\0');
		try {
			f.read(&str[0], size);
		}
		catch(std::ifstream::failure e) {
			std::cerr << "ERROR: (utls::readFile) Error reading file " << path << '\n';
		}
		f.close();
		readBuf = str.c_str();
	}
	else
		std::cerr << "ERROR: (utls::readFile) Error opening file: " << path << '\n';
}

