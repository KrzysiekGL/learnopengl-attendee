/*
 * This header contains general purpose functions.
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <atomic>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace utls {
	// Initialize random seed for the first and only time
	void initRandSeed();

	// Reads a file contents into a std::string buffer
	void readFile(std::string path, std::string & readBuf);

	// From the random list, create a random pair of adjective-noun
	std::string randomName();
}

#endif /* UTILS_HPP */

