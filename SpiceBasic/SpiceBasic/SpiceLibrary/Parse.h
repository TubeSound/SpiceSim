#ifndef _SPICE_PREPARSE_
#define _SPICE_PREPARSE_

#include "NetList.h"
#include <string>

namespace SpiceLibrary {

	class Parse
	{
	public:
		enum Kind {
			title = 0,
			blank,
			connection,
			command,
			end,
			error
		};
	public:
		Parse();
		~Parse();
		bool parseNetList(NetList& netList, std::string filepath);
		Kind parseNet(std::string netListText);
		
	};

}

#endif

