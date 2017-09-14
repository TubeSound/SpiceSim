#ifndef _SPICE_RESISTER_
#define _SPICE_RESISTER_


#include <string>
#include <vector>
#include "Component.h"
#include "Resistor.h"
#include "Value.h"

namespace SpiceLibrary {

	class Resistor: Component {

	public:
		int index;
		Value resistance;
		double conductance;

	public:
		Resistor();
		~Resistor();

	protected:	
		bool parseValue(std::vector<std::string> values);
	};

}
#endif