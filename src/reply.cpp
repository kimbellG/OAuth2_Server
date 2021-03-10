#include "../include/reply.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <map>

#include "../include/odebug.hpp"
#include "../include/http_reply_func.hpp"

namespace http
{
	Answer::Answer(const std::string &version, const std::string &code, 
		   const std::string &desrpt, const std::string &filename) 
		: __local_path(filename)
	{
		__answer = std::make_shared<std::string>();

		__answer->append(version);
		__answer->push_back(' ');
		__answer->append(code);
		__answer->push_back(' ');
		__answer->append(desrpt);
		__answer->append("\r\n");

		add_http_header("Server", server_name); //Добавление первоначальных заголовков
		add_http_header("Date", funcs::get_current_time());


#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << "\tHEADERS" << std::endl;

		for (std::vector<header>::iterator start = __http_headers.begin();
				start != __http_headers.end(); start++)
		{
			std::cout << start_mes::debug_mes << "Name: " << start->name << std::endl;
			std::cout << start_mes::debug_mes << "Value: " << start->value << std::endl;
		}
		
#endif // DEBUG_REPLY	
	}

	void Answer::add_http_header(const std::string &__name, const std::string &__value)
	{
		__http_headers.push_back({__name, __value});
	}

	std::unique_ptr<std::vector<std::string>> Answer::__get_file_to_answer()
	{
		std::string path = root_path + __local_path;
		std::string content_type;

		if (*(path.end() - 1) == '/')
		{
			path.append("index.html");
		}

		auto __data_file = std::make_unique<std::vector<std::string>>();
		std::ifstream required_file(path);
		std::string tmp;
		std::size_t content_len = 0;
		
		if (!required_file.is_open())
		{
			throw error::NotFound();	
		}

		while (std::getline(required_file, tmp))
		{
			content_len += tmp.size();
			__data_file->push_back(tmp);
		}
		add_http_header("Content-Length", std::to_string(content_len));

#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << "\t PATH" << std::endl;
		std::cout << start_mes::debug_mes << "Path: " << path << std::endl;
		
		std::cout << start_mes::debug_mes << "\t FILE" << std::endl;
		for (std::vector<std::string>::iterator ptr = __data_file->begin();
				ptr != __data_file->end(); ptr++)
		{
			std::cout << start_mes::debug_mes << *ptr << std::endl;
		}
#endif

		return __data_file;
	}

	std::shared_ptr<std::string> Answer::get_answer()
	{
		auto filedata =	__get_file_to_answer();
		
		for (std::vector<header>::iterator ptr = __http_headers.begin();
				ptr != __http_headers.end(); ptr++)
		{
			__answer->append((*ptr).name);
			__answer->append(": ");
			__answer->append((*ptr).value);
			__answer->append("\r\n");
		}
		__answer->append("\r\n");

		for (auto ptr = filedata->begin();
				ptr != filedata->end(); ptr++)
		{
			__answer->append(*ptr);
			
		}

		return __answer;
	}

	Success::Success(char *input)
		try
			: __request(input)
	{
		if (__request.version() != "HTTP/1.1")
		{
			throw error::HTTPVersionNotSupported();
		}

#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << "Creating success message" << std::endl;
#endif // DEBUG_REPLY
	}
	catch (Parser::invalid_message &e)
	{
#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << e.what() << std::endl;
#endif //DEBUG_REPLY
		throw error::BadRequest();
	}
	catch (Parser::invalid_header_name &e)
	{
#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << e.what() << std::endl;
#endif //DEBUG_REPTY
		throw error::BadRequest();
	}
	catch (Parser::invalid_method &e)
	{
#ifdef DEBUG_REPLY
		std::cout << start_mes::debug_mes << e.what() << std::endl;
#endif //DEBUG_REPLY
		throw error::HTTPVersionNotSupported();
	}

	std::shared_ptr<std::string> Success::get_answer()
	{
		Answer ans(__request.version(), "200", "OK", __request.path());
		return ans.get_answer();
	}

	namespace funcs
	{
		std::string get_current_time()
		{
			const int time_strlen = 34;
			char time_str[time_strlen];
			std::time_t t_value = std::time(NULL);
			std::tm *t_struct = std::localtime(&t_value); //Sun, 31 Jan 2021 15:55:34 GMT
			std::strftime(time_str, time_strlen, "%a, %e %b %G %H:%M:%S GMT%Z", t_struct); 
#ifdef DEBUG_REPLY
			std::cout <<  start_mes::debug_mes << "Time: " << time_str << std::endl;
#endif //DEBUG_REPLY
	
			return std::string(time_str);
		}
		
		std::string get_content_type(const std::string &path)
		{
			// Прописать выделение данного строки из конфига
			const std::map<std::string, std::string> http_type  {{"html", "text/html"},
				   	{"js", "application/javascript"}, {"css", "text/css"}};
	
			std::string type = path.substr(path.find('.'));
	
#ifdef DEBUG_REPLY
				std::cout << "Type: " << type << std::endl;
#endif // DEBUG_REPLY
	
			try
			{
				return http_type.at(type);
			} 
			catch (std::out_of_range &)
			{
				throw std::invalid_argument("Answer::content_type: Invalid_type");
			}
		}
	}
}
