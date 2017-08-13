#ifndef _STRING_UTILITIES_
#define _STRING_UTILITIES_


#include <string>
#include <stdio.h>
#include <cstdio>
#include <vector>


using namespace std;

namespace SpiceUtility {

	string trim(const string string);
	string trim2(const string string);

	bool str2bool(string s);
	std::string format(const char* fmt, ...);
	std::string i2str(std::string value, int degit);
	std::string i2str(int value, int degit);
	std::vector<std::string> split(std::string s, std::string delimiter);
	bool path2Dir(std::string path, std::string dir, std::string filename);
	std::vector<std::string> splitWithSpace(std::string text);
	std::string commentFilter(std::string spiceText);
	std::string toLower(std::string input);
	std::string toUpper(std::string input);
	bool isNumeric(const std::string& s);
	bool isPositiveInteger(const std::string& s);
}

#endif