#include "Component.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	const int letters_size = 6;
	std::string letters[letters_size] = { "R", "C", "L", "I", "V", "?"};
	
	Component::Component() {
	}

	Component::~Component() {
	}

	bool Component::parse(std::string componentText) {
		std::vector<std::string> values = splitWithSpace(componentText);
		if (values.size() < 4) {
			return false;
		}

		string letter = values[0].substr(0, 1);
		this->identifier = componentText.substr(1, componentText.length() - 1);
		this->type = whichType(letter);
		
		if (!parseValue(values)) {
			return false;
		}

		return true;
	}

	ComponentType Component::whichType(std::string text) {
		ComponentType type = ComponentType::undefined;
		if (text.length() < 1) {
			return type;
		}
		std::string letter = text.substr(0, 1);
		for (int i = 0; i < letters_size; i++) {
			std::string s = letters[i];
			if (toLower(s) == toLower(letter)) {
				type = static_cast<ComponentType> (i);
				break;
			}
			i++;
		}
		return type;
	}

	std::string Component::name() {
		switch (this->type) {
			case ComponentType::resistance:
				return "Resistor";
				break;
			case ComponentType::capacitor:
				return "Capacitor";
				break;
			case ComponentType::reactance:
				return "Reactance";
				break;
			case ComponentType::currentSource:
				return "CurrentSource";
				break;
			case ComponentType::voltageSource:
				return "VoltageSource";
				break;
			default:
				return "no name";
				break;
		}
	}

	Range Component::elementSize() {
		switch (this->type) {
			case ComponentType::resistance:
			case ComponentType::capacitor:
			case ComponentType::reactance:
				return Range(4, 4);
				break;
			case ComponentType::voltageSource:
			case ComponentType::currentSource:
				return Range(4, 5);
				break;
			default:
				return Range(0, 0);
				break;
		}
	}


	std::string Component::letter(int index) {
		switch (index) {
			case ComponentType::resistance:
				return "R";
				break;
			case ComponentType::capacitor:
				return "C";
				break;
			case ComponentType::reactance:
				return "L";
				break;
			case ComponentType::currentSource:
				return "I";
				break;
			case ComponentType::voltageSource:
				return "V";
				break;
			default:
				return "no name";
				break;
		}
	}

}