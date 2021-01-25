#ifndef __OUTPUT_DEBUG_MESSAGE__
#define __OUTPUT_DEBUG_MESSAGE__


#include <iostream>
#include <iomanip>

namespace start_mes
{
	inline std::ostream &debug_mes(std::ostream &out)
	{
		out << "[DEBUG] | ";
		return out;
	}
	
	inline std::ostream &start_err_mes(std::ostream &out)
	{
		out << "[ERROR] | ";
		return out;
	}
}

#endif //__OUTPUT_DEBUG_MESSAGE__
