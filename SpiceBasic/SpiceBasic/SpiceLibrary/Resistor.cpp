#include "Resistor.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {


	Resistor::Resistor() {
		this->type = ComponentType::resistor;
	}

	Resistor::~Resistor() {
	}

	bool Resistor::parseValue(std::vector<std::string> values) {
		if (values.size() < 4) {
			return false;
		}

		Value val;
		bool ret = val.parse(values[3]);
		if (ret && val.value != 0.0) {
			this->resistance = val.value;
			this->conductance = 1.0 / val.value;
			return true;
		} else {
			return false;
		}
	}

}