#include "Node.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	Node::Node(){
		this->index = -1;
	}

	Node::~Node(){
	}

	bool Node::parse(std::string nodeText) {
		string trimmed = trim(nodeText);
		if (trimmed.length() == 0) {
			return false;
		}
		this->name_ = trimmed;
		return true;
	}
}