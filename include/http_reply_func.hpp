#ifndef __HTTP_REPLY_FUNC_HPP__
#define __HTTP_REPLY_FUNC_HPP__


#include <string>

namespace http
{
	namespace funcs
	{
		std::string get_current_time();
		std::string get_content_type(const std::string &path);
	}
}

#endif  // __HTTP_REPLY_FUNC_HPP__
