#include "utils.hpp"
#include "random-words.hpp"

void utls::initRandSeed() {
	static std::atomic<bool> srandIssued = false;
	bool expected = false;
	if(srandIssued.compare_exchange_strong(expected, true))
		srand(time(NULL));
}

void utls::readFile(std::string path, std::string & readBuf) {
	std::ifstream f(path, std::ios::ate);
	if(f.is_open()) {
		auto size = f.tellg();
		f.seekg(0);
		std::string str(size, '\0');
		try {
			f.read(&str[0], size);
		}
		catch(const std::ifstream::failure & e) {
			std::cerr << "ERROR: (utls::readFile) Excetption error reading file " << path << '\n'
								<< "Explanatory string: " << e.what() << '\n'
								<< "Error code: " << e.code() << '\n';
			f.close();
			throw;
		}
		f.close();
		readBuf = str.c_str();
	}
	else {
		std::cerr << "ERROR: (utls::readFile) Error opening file: " << path << '\n';
		throw std::ios_base::failure("Error opening file\n");
	}
}

std::string utls::randomName() {
	initRandSeed();

	std::string str;
	str = randomAdjective[rand() % LIST_SIZE];
	str += '-';
	str += randomNoun[rand() % LIST_SIZE];

	return str;
}


