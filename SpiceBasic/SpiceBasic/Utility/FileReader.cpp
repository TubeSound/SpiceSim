#include "FileReader.h"
#include "StringUtility.h""

using namespace SpiceUtility;

namespace SpiceUtility {

	FileReader::FileReader(std::string filepath)
	{
		this->file.open(filepath.c_str(), std::ios::out);
		this->isOpen = (!this->file) ? false : true;
	}

	FileReader::~FileReader()
	{
		close();
	}

	bool FileReader::read(string& text) {
		if (this->isOpen) {
			if (this->file.eof()) {
				return false;
			}
			string line;
			std::getline(this->file, line);
			if (line.size() > 1) {
				char last = line[line.size() - 1];
				if (last == '\n' || last == '\r') {
					text = line.substr(0, line.size() - 1);
				}
				else {
					text = line;
				}
			}
			else {
				text = line;
			}
			return true;
		}
		return false;
	}

	bool FileReader::read(std::vector<std::vector<std::string>>& list) {
		if (this->isOpen) {
			if (this->file.eof()) {
				return false;
			}
			std::string line;
			std::getline(this->file, line);
			std::string delimiter = " ";
			std::vector<std::string> result = split(line, delimiter);
		}
		return false;
	}

	void FileReader::close() {
		if (this->file) {
			this->file.close();
			this->isOpen = false;
		}
	}

}