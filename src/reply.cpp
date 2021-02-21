#include "../include/reply.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <ctime>

#include "../include/odebug.hpp"

namespace http
{
	Answer::Answer(char *input, const char *server_name) 
		try
			: __request(input), __server_name(server_name), __code(OK)
	{
		const int time_strlen = 34;
		char time_str[time_strlen];
		std::time_t t_value = std::time(NULL);
		std::tm *t_struct = std::localtime(&t_value); //Sun, 31 Jan 2021 15:55:34 GMT
		std::strftime(time_str, time_strlen, "%a, %e %b %G %H:%M:%S GMT%Z", t_struct); 
#ifdef DEBUG_REPLY
		std::cout <<  start_mes::debug_mes << "Time: " << time_str << std::endl;
#endif //DEBUG_REPLY


		__add_version(); // Добавление версии
		__add_http_header("Server", server_name); //Добавление первоначальных заголовков
		__add_http_header("Date", time_str);
		__add_file_to_answer();
#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << "\tHEADERS" << std::endl;

		for (std::vector<header>::iterator start = __http_headers.begin();
				start != __http_headers.end(); start++)
		{
			std::cout << start_mes::debug_mes << "Name: " << start->name << std::endl;
			std::cout << start_mes::debug_mes << "Value: " << start->value << std::endl;
		}
		
		std::cout << start_mes::debug_mes << "Code: " << __code << std::endl;
#endif // DEBUG_REPLY	
	}
	catch (Parser::invalid_message &e)
	{
		std::cerr << start_mes::debug_mes << "Invalid message" << std::endl;
		throw;
	}

	void Answer::__add_version()
	{
		__version = __request.version();

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

	void Answer::__add_file_to_answer()
	{
		std::string path = root_path + __request.path();
		std::string content_type;

		if (*(path.end() - 1) == '/')
		{
			path.append("index.html");
		}

		std::ifstream required_file(path);
		std::string tmp;
		std::size_t content_len = 0;
		

		if (required_file.is_open())
		{

			while (std::getline(required_file, tmp))
			{
				content_len += tmp.size();
				__data_file.push_back(tmp);
			}
			__add_http_header("Content-Length", std::to_string(content_len));
		}
		else
		{
			__code = Not_Found;
		}

#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << "\t PATH" << std::endl;
		std::cout << start_mes::debug_mes << "Path: " << path << std::endl;
		
		std::cout << start_mes::debug_mes << "\t FILE" << std::endl;
		for (std::vector<std::string>::iterator ptr = __data_file.begin();
				ptr != __data_file.end(); ptr++)
		{
			std::cout << start_mes::debug_mes << *ptr << std::endl;
		}
#endif
	}

	std::unique_ptr<std::string> Answer::get_answer()
	{
		std::unique_ptr<std::string> answer = std::make_unique<std::string>();

		return answer;
	}
	
}
