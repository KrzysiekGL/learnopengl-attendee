/*
 * This header contains general purpose functions.
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
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

