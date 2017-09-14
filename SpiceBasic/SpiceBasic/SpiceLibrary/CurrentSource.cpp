#include "CurrentSource.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {


	CurrentSource::CurrentSource() {
		this->type = ComponentType::currentSource;
	}

	CurrentSource::~Resistor() {
	}

	bool CurrentSource::parseValue(std::vector<std::string> values) {
		if (values.size() < 4) {
			return false;
		}

		Value val;
		bool ret = val.parse(values[3]);
		this->current = val;
		return ret;
	}

}