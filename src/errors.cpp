#include "../include/errors.hpp"

#include <iostream>

namespace http
{
	namespace error
	{
		Error::Error(const std::string &code, const std::string &err_message,
				const std::string &filename) 
			: __code(code), __err_message(err_message), __filename(filename)
		{

		}


	}
}
