#include "../include/reply.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

#include "../include/odebug.hpp"

namespace http
{
	Answer::Answer(char *input, const char *server_name) 
		: request(input), __server_name(server_name), __code(OK)
	{
		const int time_strlen = 32;
		char time_str[time_strlen];
		std::time_t t_value = std::time(NULL);
		std::tm *t_struct = std::localtime(&t_value); //Sun, 31 Jan 2021 15:55:34 GMT
		std::strftime(time_str, time_strlen, "%a, %e %b %G %H:%M:%S %Z", t_struct); 
#ifdef DEBUG_REPLY
		std::cout <<  start_mes::debug_mes << "Time: " << time_str << std::endl;
#endif //DEBUG_REPLY


		__add_version(); // Добавление версии
		__add_http_header("Server", server_name); //Добавление первоначальных заголовков
		__add_http_header("Date", time_str);
		// __add_file_to_answer();
#ifdef DEBUG_REPLY
		std::cout << "\tHEADERS" << std::endl;

		for (std::vector<header>::iterator start = __http_headers.begin();
				start != __http_headers.end(); start++)
		{
			std::cout << "Name: " << start->name << std::endl;
			std::cout << "Value: " << start->value << std::endl;
		}
#endif // DEBUG_REPLY	
	}

	void Answer::__add_version()
	{
		try
		{
			__version = request.version();
		}
		catch (Parser::exeptions &e)
		{
			if (e == Parser::exeptions::invalid_message)
			{
				__code = Bad_Request;
			}
		}

		if (__version != "HTTP/1.1")
		{
			__code = HTTP_Version_Not_Supported;
		}

#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << "\tGET VERSION" << std::endl;
		std::cout << start_mes::debug_mes << "Ver: " << __version << std::endl;
		std::cout << start_mes::debug_mes << "Code: " << __code << std::endl;
#endif //DEBUG_REPLY
	}

	void Answer::__add_http_header(std::string __name, std::string __value)
	{
		__http_headers.push_back({__name, __value});
	}
}
