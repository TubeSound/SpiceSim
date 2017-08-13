#include "Model.h"
#include "../Utility/StringUtility.h"

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	Model::Model()
	{
		this->prefixes.clear();
		for (int i = 0; i < ModelType::length; i++) {
			this->prefixes.push_back(prefix(i));
		}
	}

	Model::~Model()
	{
	}

	bool Model::parse(std::string modelText) {
		if (modelText.length() <= 1) {
			return false;
		}
		string prefix = modelText.substr(0, 1);
		this->identifier = modelText.substr(1, modelText.length() - 1);
		return whichType(prefix);
	}

	bool Model::whichType(std::string prefix) {
		int i = 0;
		bool found = false;
		for (string s : this->prefixes) {
			if (toLower(s) == toLower(prefix)) {
				this->type = static_cast<ModelType> (i);
				found = true;
				break;
			}
			i++;
		}
		return found;
	}

	std::string Model::name() {
		switch (this->type) {
			case ModelType::resistance:
				return "Resistor";
				break;
			case ModelType::capacitor:
				return "Capacitor";
				break;
			case ModelType::reactance:
				return "Reactance";
				break;
			case ModelType::currentSource:
				return "CurrentSource";
				break;
			case ModelType::voltageSource:
				return "VoltageSource";
				break;
			default:
				return "no name";
				break;
		}
	}

	Range Model::elementSize() {
		switch (this->type) {
			case ModelType::resistance:
			case ModelType::capacitor:
			case ModelType::reactance:
				return Range(4, 4);
				break;
			case ModelType::voltageSource:
			case ModelType::currentSource:
				return Range(4, 5);
				break;
			default:
				return Range(0, 0);
				break;
		}
	}

	std::string Model::prefix() {
		return prefix(this->index);
	}

	std::string Model::prefix(int index) {
		switch (index) {
			case ModelType::resistance:
				return "R";
				break;
			case ModelType::capacitor:
				return "C";
				break;
			case ModelType::reactance:
				return "L";
				break;
			case ModelType::currentSource:
				return "I";
				break;
			case ModelType::voltageSource:
				return "V";
				break;
			default:
				return "no name";
				break;
		}
	}

}