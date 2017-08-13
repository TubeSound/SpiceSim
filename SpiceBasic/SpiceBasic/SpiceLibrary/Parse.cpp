#include "Parse.h"
#include "../Utility/StringUtility.h"
#include "../Utility/FileReader.h"
#include "Model.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {
	Parse::Parse()
	{
	}

	Parse::~Parse()
	{
	}

	bool Parse::parseNetList(NetList& netlist, std::string filepath) {
		FileReader reader(filepath);
		string line;
		if (reader.read(line)) {
			netlist.title = line;
		}
		while (reader.read(line)) {
			Kind kind = parseNet(line);
			if (kind == Kind::connection) {
				if (!netlist.parse(line)) {
					// error process
				}
			}
			else if (kind == Kind::error) {
				// error process
			}
			else if (kind == Kind::command) {
				// command process
			}
			else if (kind == Kind::end) {
				break;
			}
		}

		return true;
	}

	Parse::Kind Parse::parseNet(std::string netListText) {
		string trimmed = commentFilter(netListText);
		if (trimmed.length() == 0) {
			return Parse::Kind::blank;
		}

		if (trimmed == ".end") {
			return Parse::Kind::end;
		}
		
		string s = trimmed.substr(0, 1);
		if (s == ".") {
			return Parse::Kind::command;
		}
		
		vector<string> elements = splitWithSpace(trimmed);
		if (elements.size() == 0) {
			return Parse::Kind::blank;
		}

		Model model;
		if (model.parse(elements[0])) {
			if (model.elementSize().involve(elements.size())) {
				return Parse::Kind::connection;
			}
		} 

		return Parse::Kind::error;
	}
}