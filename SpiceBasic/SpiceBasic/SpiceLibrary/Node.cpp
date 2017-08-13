#include "Node.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	Node::Node()
	{
	}

	Node::~Node()
	{
	}

	bool Node::parse(std::string nodeText) {
		string trimmed = trim(nodeText);
		if (trimmed.length() == 0) {
			return false;
		}
		this->name = trimmed;
		return true;
	}
}