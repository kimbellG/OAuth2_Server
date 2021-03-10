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
		std::shared_ptr<std::string> __answer;
		std::vector<header> __http_headers;
		std::string __local_path;
		
		std::unique_ptr<std::vector<std::string>> __get_file_to_answer();
	public:
		Answer(const std::string &version, const std::string &code, const std::string &desrpt,
			   const std::string &filename);

		void add_http_header(const std::string &__name, const std::string &__value);
		std::shared_ptr<std::string> get_answer();
	
		~Answer()
		{
		}
	};

	class Success
	{
		Parser __request;

	public:
		Success(char *input);

		std::shared_ptr<std::string> get_answer();
		
		~Success()
		{
		}
	};
}

#endif // __REPLY_SERVER__
