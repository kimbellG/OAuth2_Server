#ifndef __REPLY_SERVER__
#define __REPLY_SERVER__


#define DEBUG_REPLY

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "parsing.hpp"
#include "errors.hpp"

namespace http
{

	extern std::string root_path;
	extern std::string config;
	extern std::string server_name;

	class Answer
	{
		std::unique_ptr<Parser> __request;

		std::vector<header> __http_headers;

		std::string __version();
		void __add_http_header(std::string __name, std::string __value);
		std::unique_ptr<std::vector<std::string>> __get_file_to_answer();

	public:
		Answer(char *input);

		std::unique_ptr<std::string> get_answer();
	
		~Answer();
	};
}

#endif // __REPLY_SERVER__
