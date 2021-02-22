#ifndef __REPLY_SERVER__
#define __REPLY_SERVER__


#define DEBUG_REPLY

#include <vector>
#include <string>
#include <iostream>

#include "parsing.hpp"
#include "errors.hpp"

namespace http
{

	extern std::string root_path;
	extern std::string config;
	extern std::string server_name;

	class Answer
	{
		Parser __request;

		std::string __version;
		std::vector<std::string> __data_file;

		std::vector<header> __http_headers;

		error::Error *__error;

		void __add_file_to_answer();
		void __add_version();
		void __add_http_header(std::string __name, std::string __value);

		std::string __get_content_type(std::string path)
		{
			const std::vector<std::string> http_type = {"html",	"text/html","js", "application/javascript",
			   	"css", "text/css"};

			std::string type = path.substr(path.find('.'));

#ifdef DEBUG_REPLY
			std::cout << "Type: " << type << std::endl;
#endif // DEBUG_REPLY

			for (std::vector<std::string>::const_iterator ptr = http_type.begin();
					ptr != http_type.end(); ptr++)
			{
				if (type == *ptr)
				{
					return *(ptr + 1);
				}
			}
			throw std::invalid_argument("Answer::content_type: Invalid_type");
		}

	public:
		Answer(char *input);

		static std::string get_current_time();

		std::unique_ptr<std::string> get_answer();
	
		~Answer();
	};
}

#endif // __REPLY_SERVER__
