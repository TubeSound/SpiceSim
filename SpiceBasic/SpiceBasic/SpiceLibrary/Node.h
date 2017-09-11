#ifndef _SPICE_NODE_
#define _SPICE_NODE_

#include <string>

namespace SpiceLibrary {

	class Node
	{
		private:
			std::string name_;
			
		public:
			int index;

			Node();
			~Node();

			bool parse(std::string nodeText);
			void setIndex(int index) {this->index = index;};
			std::string name() {return this->name_;};
	};

}

#endif

