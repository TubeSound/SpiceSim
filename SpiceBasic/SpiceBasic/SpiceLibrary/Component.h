#ifndef _SPICE_COMPONENT_
#define _SPICE_COMPONENT_


#include <string>
#include <vector>

namespace SpiceLibrary {

	enum ComponentType {
		resistance = 0,
		capacitor = 1,
		reactance = 2,
		currentSource = 3,
		voltageSource = 4,
		length = 5
	};

	class Range {
		public:
			int lower;
			int higher;

		public:
			Range(int lower, int higher) {
				if (higher > lower) {
					this->lower = lower;
					this->higher = higher;
				}
				else {
					this->lower = higher;
					this->higher = lower;
				}
			}

			bool involve(Range range) {
				return (range.lower >= this->lower && range.higher <= this->higher);
			}

			bool involve(int value) {
				return (value >= this->lower && value <= this->higher);
			}
	};

	class Component {

	public:
		int index;
		ComponentType type;
		std::string identifier;
		std::vector<std::string> letters;

	public:
		Component();
		~Component();
		bool parse(std::string componentText);
		Range elementSize();

	private:
		std::string name();
		std::string letter(int index);
		bool whichType(std::string letter);
	};

}
#endif