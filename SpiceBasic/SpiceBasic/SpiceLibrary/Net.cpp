#include "Net.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	Net::Net() {
	}

	Net::~Net() {
	}

	bool Net::parse(std::string netText) {
		string trimmed = commentFilter(netText);
		vector<string> elements = splitWithSpace(trimmed);
		Model model;
		if (!model.parse(elements[0])) {
			return false;
		}
		Node in;
		if (!in.parse(elements[1])) {
			return false;
		}
		Node out;
		if (!out.parse(elements[2])) {
			return false;
		}

		Value value;
		if (elements.size() == 4) {
			this->option = "";
			if (!value.parse(elements[3])) {
				return false;
			}
		} else {
			this->option = elements[3];
			if (!value.parse(elements[4])) {
				return false;
			}
		}

		this->model = model;
		this->inNode = in;
		this->outNode = out;
		this->value = value;

		return true;
	}


}