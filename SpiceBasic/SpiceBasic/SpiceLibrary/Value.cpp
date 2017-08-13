#include "Value.h"
#include "../Utility/StringUtility.h"
#include <string>

using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	Value::Value()
	{
	}

	Value::~Value()
	{
	}

	bool Value::parse(std::string valueText) {
		const int size = 6;
		string powerString[] = { "meg", "k", "m", "u", "p", "n" };
		double power[] = { 1.0e6, 1.0e3, 1.0e-3, 1.0e-6, 1.0e-9, 1.0e-12 };

		string trimmed = toLower(trim(valueText));
		if (trimmed.length() == 0) {
			return false;
		}

		if (isNumeric(trimmed)) {
			this->value = std::stod(trimmed);
			this->valueString = trimmed;
			return true;
		}

		if (trimmed.length() == 1) {
			return false;
		}

		int pos;
		int index;
		for (int i = 0; i < size; i++) {
			pos = trimmed.find(powerString[i]);
			if (pos >= 0) {
				index = i;
				break;
			}
		}
		
		string figure;
		if (pos >= 0) {
			figure = trimmed.substr(0, pos);
		}

		if (isNumeric(figure)) {
			this->value = power[index] * std::stod(figure);
			this->valueString = trimmed;
			return true;
		} else {
			return false;
		}
	}
}