#ifndef _SPICE_CURRENT_SOURCE_
#define _SPICE_CURRENT_SOURCE_


#include <string>
#include <vector>
#include "Component.h"
#include "Value.h"

namespace SpiceLibrary {

	class CurrentSource: Component {

	public:
		int index;
		Value current;

	public:
		CurrentSource();
		~CurrentSource();

    protected:    
		bool parseValue(std::vector<std::string> values);


	};

}
#endif