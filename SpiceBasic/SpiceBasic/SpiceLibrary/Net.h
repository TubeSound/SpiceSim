#ifndef _SPICE_NET_
#define _SPICE_NET_

#include <string>
#include "Model.h"
#include "Node.h"
#include "Value.h"

namespace SpiceLibrary {

	class Net
	{
		public:
			int index;
			Model model;
			Node inNode;
			Node outNode;
			std::string option;
			Value value;

		public:
			Net();
			~Net();
			bool parse(std::string netText);
			Net outNet(int index);
	};

}

#endif