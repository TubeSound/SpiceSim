#ifndef _SPICE_VALUE_
#define _SPICE_VALUE_

#include <string>

namespace SpiceLibrary {
	class Value
	{
	public :
		double value;
		std::string valueString;

	public:
		Value();
		~Value();
		bool parse(std::string valueText);
	};

}

#endif
