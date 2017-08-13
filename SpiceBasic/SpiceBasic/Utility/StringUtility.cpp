#include "StringUtility.h"
#include <stdarg.h>
#include <algorithm>
#include <cctype> 

using namespace std;

namespace SpiceUtility {

	string trim(const string string) {
		const char* trimCharacterList = " \t\v\r\n";
		std::string s;
		string::size_type left = string.find_first_not_of(trimCharacterList);
		if (left != std::string::npos) {
			string::size_type right = string.find_last_not_of(trimCharacterList);
			s = string.substr(left, right - left + 1);
		}
		return s;
	}

	string trim2(const string str) {
		char chars[] = { '\t', '\v', '\r', '\n', ' ', '"' };
		std::string sub;
		std::string out = "";
		for (unsigned int i = 0; i < str.size(); i++) {
			sub = str.substr(i, 1);
			bool found = false;
			for (int j = 0; j < 6; j++) {
				string c{ chars[j] };
				if (sub.compare(c) == 0) {
					found = true;
					break;
				}
			}
			if (!found) {
				out += sub;
			}
		}
		return out;
	}

	bool str2bool(string s) {
		int i = std::atoi(s.c_str());
		return (i != 0);
	}

	std::string format(const char* fmt, ...) {
		va_list vl;
		va_start(vl, fmt);
		int size = vsnprintf(0, 0, fmt, vl) + sizeof('\0');
		va_end(vl);
		char* buffer = new char[size];
		va_start(vl, fmt);
		size = vsnprintf(buffer, size, fmt, vl);
		va_end(vl);
		std::string s = std::string(buffer, size);
		delete buffer;
		return s;
	}

	std::string i2str(std::string value, int degit) {
		std::string s;
		for (int i = 0; i < degit; i++) {
			s += "0";
		}
		s += value;
		return s.substr(s.length() - degit, degit);
	}

	std::string i2str(int value, int degit) {
		std::string v = format("%d", value);
		return i2str(v, degit);
	}

	std::vector<std::string> split(std::string s, std::string delimiter) {
		std::vector<std::string> out;
		out.clear();
		string::size_type pos = 0;
		while (pos != string::npos) {
			string::size_type p = s.find(delimiter, pos);
			if (p == string::npos) {
				out.push_back(trim(s.substr(pos)));
				break;
			}
			else {
				out.push_back(trim(s.substr(pos, p - pos)));
			}
			pos = p + delimiter.size();
		}
		return out;
	}

	bool path2Dir(std::string path, std::string dir, std::string filename) {
		int p = path.rfind("/");
		if (p >= 0) {
			dir = path.substr(0, p + 1);
			filename = path.substr(p + 1, path.size() - p - 1);
		}
		else {
			dir = "";
			filename = path;
		}
		return true;
	}

	std::vector<std::string> splitWithSpace(std::string text) {
		std::string delimiter = " ";
		std::vector<std::string> out;
		out.clear();

		std::string str = "";
		bool spaceIn = false;
		for (int i = 0; i < text.length(); i++) {
			std::string s = text.substr(i, 1);
			if (s == delimiter) {
				if (!spaceIn) {
					spaceIn = true;
					if (i != 0) {
						out.push_back(str);
						str = "";
					}
				}
			} else {
				str += s;
				if (spaceIn) {
					spaceIn = false;
				}
			}
		}
		out.push_back(str);
		return out;
	}

	std::string commentFilter(std::string spiceText) {
		std::string trimmed = trim(spiceText);
		int p = trimmed.find('*');
		if (p < 0) {
			return trimmed;
		} else {
			return trimmed.substr(0, p);
		}
	}

	std::string toLower(std::string input) {
		string output = input;
		transform(output.cbegin(), output.cend(), output.begin(), tolower);
		return output;
	}

	std::string toUpper(std::string input) {
		string output = input;
		transform(output.cbegin(), output.cend(), output.begin(), toupper);
		return output;
	}

	// true : 123  -123 123.4  1.23e10 1.23e-1
	bool isNumeric(const std::string& s) {
		if (s.empty() || std::isspace(s[0]) || std::isalpha(s[0])) return false;
		char * p;
		strtod(s.c_str(), &p);
		return (*p == 0);
	}

	bool isPositiveInteger(const std::string& s) {
		bool result = true;
		for (int i = 0; i < s.length(); i++) {
			unsigned char c = static_cast<unsigned char>(s.at(i));
			if (!isdigit(c)) {
				result = false;
			}
		}
		return result;
	}
}

