#include "Component.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	Component::Component() {
		this->letters.clear();
		for (int i = 0; i < ComponentType::length; i++) {
			this->letters.push_back(letter(i));
		}
	}

	Component::~Component() {
	}

	bool Component::parse(std::string componentText) {
		if (componentText.length() <= 1) {
			return false;
		}
		string letter = componentText.substr(0, 1);
		this->identifier = componentText.substr(1, componentText.length() - 1);
		return whichType(letter);
	}

	bool Component::whichType(std::string letter) {
		int i = 0;
		bool found = false;
		for (string s : this->letters) {
			if (toLower(s) == toLower(letter)) {
				this->type = static_cast<ComponentType> (i);
				found = true;
				break;
			}
			i++;
		}
		return found;
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