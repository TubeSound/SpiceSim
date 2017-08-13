#ifndef _SPICE_MODEL_
#define _SPICE_MODEL_


#include <string>
#include <vector>

namespace SpiceLibrary {

	enum ModelType {
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

	class Model
	{

	public:
		int index;
		ModelType type;
		std::string identifier;
		std::vector<std::string> prefixes;

	public:
		Model();
		~Model();
		bool parse(std::string modelText);
		Range elementSize();

	private:
		std::string name();
		std::string prefix();
		std::string prefix(int index);
		bool whichType(std::string prefix);
	};

}
#endif