/*
 * This header contains general purpose functions.
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace utls {
	// Reads a file contents into a std::string buffer
	void readFile(std::string path, std::string & readBuf);
}

#endif /* UTILS_HPP */

