#include "../include/errors.hpp"

#include <iostream>

#include "../include/reply.hpp"

namespace http
{
	namespace error
	{
		Error::Error(const std::string &code, const std::string &err_message,
				const std::string &filename) 
			: __code(code), __err_message(err_message), __filename(filename)
		{
			__http_headers = std::make_shared<std::vector<header>>();

			add_header("Server", server_name);
			add_header("Time", Answer::get_current_time());
		}

		void Error::add_header(const std::string &name, const std::string &value)
		{
			__http_headers->push_back({name, value});
		}

		std::unique_ptr<std::string> Error::get_answer() const
		{
		}

		Error::~Error()
		{
		}
	}
}
