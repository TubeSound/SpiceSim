#ifndef _SPICE_FILE_READER_
#define _SPICE_FILE_READER_

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace SpiceUtility{

class FileReader
{
public:
	FileReader(std::string filePath);
	bool read(std::string& text);
	bool read(std::vector<std::vector<std::string>>& list);
	~FileReader();

private:
	std::ifstream file;
	bool isOpen;
	void close();
};

}
#endif