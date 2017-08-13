#ifndef _SPICE_NODE_
#define _SPICE_NODE_

#include <string>

namespace SpiceLibrary {
	enum NodeType {
		normal = 0,
		ground = 1
	};

	class Node
	{
		public:
			int index;
			NodeType type;
			std::string name;

		public:
			Node();
			~Node();
			bool parse(std::string nodeText);
	};

}

#endif

