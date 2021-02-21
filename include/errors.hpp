#ifndef __ERRORS_TYPE_HPP__
#define __ERRORS_TYPE_HPP__

#include <iostream>
#include <vector>
#include <memory>

#include "parsing.hpp"

namespace http
{
	namespace error
	{
		class Error
		{
			std::string __code;
			std::string __err_message;
			std::shared_ptr<std::vector<header>> __http_headers;
			

		public:
			Error();

			virtual std::unique_ptr<std::string> get_answer() const;

			~Error();
		};
	}
}



#endif //__ERRORS_TYPE_HPP__
