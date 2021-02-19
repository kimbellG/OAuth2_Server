#ifndef __REPLY_SERVER__
#define __REPLY_SERVER__


#define DEBUG_REPLY

#include <vector>
#include <string>

#include "parsing.hpp"

namespace http
{

	extern std::string root_path;
	extern std::string config;

	class Answer
	{
		Parser __request;

		const char* __server_name;

		std::string __version;
		std::vector<std::string> __data_file;

		std::vector<header> __http_headers;

		void __add_file_to_answer();
		void __add_version();
		void __add_http_header(std::string __name, std::string __value);

		enum __status_code
		{
			OK = 200,
			Bad_Request = 400,
			Forbidden  = 403,
			Not_Found = 404,
			Method_Not_Allowed = 405,
			Length_Required = 411,
			Not_Implemented = 501,
			HTTP_Version_Not_Supported = 505
		} __code;

	public:
		Answer(char *input, const char *server_name = "FServ");

		std::string get_answer();
	
		~Answer();
	};
}

#endif // __REPLY_SERVER__
