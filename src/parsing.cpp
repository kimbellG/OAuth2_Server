#include "../include/parsing.hpp"

#include <iostream>
#include <cstring>

#include "../include/odebug.hpp"

namespace http
{
	Parser::Parser(std::string input)
	{
		int curr_pos = 0;

		__start_processing(input, curr_pos); 

		__http_headers_processing(input, curr_pos);

		__data__processing(input, curr_pos);

		__nhttp_headers_proccesing();
	
	}

	void Parser::__start_processing(const std::string &input, int &start_request)
	{
		size_t end_word;
		for (int i = 0; i < __value_element::__number_elements; i++)
		{
			end_word = input.find((i == __version) ? '\r' : ' ', start_request);

			if (end_word == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::__start_processing()." 
					<< "Invalid message from client."
					<< "Not found - ' ', '\\r'" << std::endl;
				__basic_elements[i].clear();
				start_request = -1;
				return;
			}

			__basic_elements[i] = input.substr(start_request, end_word - start_request);
			start_request = end_word + 1;

		}

#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "Method: " << __basic_elements[__method] << std::endl;
		std::cout << start_mes::debug_mes << "Path: " << __basic_elements[__path] << std::endl;
		std::cout << start_mes::debug_mes << "Version: " << __basic_elements[__version] << std::endl;
#endif // DEBUG_HEADER

	}

	void Parser::__http_headers_processing(const std::string &input, int &start_headers)
	{

		if (start_headers == -1)
		{
			__http_headers.clear();
			return;
		}

		std::size_t end_word;	
		std::string header_str;
		header tmp;
		end_word = input.find('\n', ++start_headers); 
	
		if (end_word == std::string::npos)
		{
			std::cerr << start_mes::start_err_mes << "Parser::__http_headers_processing()."
			   << "Not found: '\\n'" << std::endl;
			__http_headers.clear();
			start_headers = -1;
			return;
		}
	
	
		while ((header_str = input.substr(start_headers, end_word - start_headers)) != "\r")
		{
			start_headers = end_word + 1;
			end_word = input.find('\n', start_headers);
			if (end_word == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::__http_headers_processing()."
				   << "Not found: '\\n'" << std::endl;
				__http_headers.clear();
				start_headers = -1;
				return;
			}
			
	#ifdef DEBUG_TMP
			std::cout << start_mes::debug_mes << header_str << std::endl;
	#endif //DEBUG_HEADER
	
			std::size_t value_start = header_str.find(':');
			if (value_start == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::__http_headers_processing. "
				   << "Not found: ':' in header's pars" << std::endl;
				__http_headers.clear();
				start_headers = -1;
				return;
			}

			tmp.name = header_str.substr(0, value_start);
			tmp.value = header_str.substr(value_start + 2, header_str.size() - value_start);
	
			__http_headers.push_back(tmp);
		}
#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "\tHTTP HEADERS" << std::endl;

		for (std::size_t i = 0; i < __http_headers.size(); i++)
		{
			std::cout << start_mes::debug_mes 
				<< "Name = " << __http_headers[i].name << std::setw(10) 
				<< "Value = " << __http_headers[i].value << std::endl;
		}
#endif //DEBUG_HEADER
	}

	void Parser::__data__processing(const std::string &input, int &start_data)
	{
		if (start_data == -1)
		{
			__data.clear();
			return;
		}

		start_data += 2;

		__data = input.substr(start_data, input.size() - start_data);

#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "\tDATA" << std::endl
		   	<<  start_mes::debug_mes << __data << std::endl;
#endif //DEBUG_HEADER
	}

	void Parser::__nhttp_headers_proccesing()
	{
		std::size_t start_headers;
		std::string headers;

		try
		{
			if (method() == "GET")
			{
				 start_headers = __basic_elements[__value_element::__path].find('?');
				
				if (start_headers == std::string::npos)
				{
					return;
				}
				
				start_headers++;
				headers = __basic_elements[__value_element::__path].substr(start_headers, __basic_elements[__value_element::__path].size() - start_headers);
				__basic_elements[__value_element::__path].erase(start_headers);
			}
		   	else if (method() == "POST" && http_header("Content-Type") == "application/x-www-form-urlencoded\r")
			{
				headers = __data;
	#ifdef DEBUG_TMP
				std::cout << start_mes::debug_mes  
				   <<	"method - POST, content-type == application/x-www-form-urlencoded" << std::endl;
	#endif //DEBUG_HEADER
	
			}
		}
		catch (exeptions &e)
		{
			return;
		}

		if (headers.empty())
		{
			return;
		}
			
		start_headers = 0;
		std::size_t end_headers;
		header tmp;
		do
		{
			end_headers = headers.find('&', start_headers);
			std::size_t end_name = headers.find('=', start_headers);

			tmp.name = headers.substr(start_headers, end_name - start_headers);
			tmp.value = headers.substr(end_name + 1, end_headers - end_name - 1);
			__not__http_headers.push_back(tmp);

			start_headers = end_headers + 1;
#ifdef DEBUG_TMP
			std::cout << start_mes::debug_mes << "Name: " << tmp.name << std::endl;
			std::cout << start_mes::debug_mes << "Value: " << tmp.value << std::endl;
#endif //DEBUG_TMP

		} while (end_headers != std::string::npos);
#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "\tNON HTTP HEADERS" << std::endl;

		std::vector<header>::iterator start = __not__http_headers.begin();	
		while (start != __not__http_headers.end())
		{
			std::cout << start_mes::debug_mes << "Name: " << start->name << std::endl;
			std::cout << start_mes::debug_mes << "Value: " << start->value << std::endl;
			start++;
		}
#endif // DEBUG_HEADER
		

	}

	std::string Parser::path()
	{
		if (__basic_elements[__value_element::__path].empty())
		{
			throw invalid_message;
		}

		std::size_t end_path = __basic_elements[__value_element::__path].find('?');
		if (end_path == std::string::npos)
		{
			return __basic_elements[__value_element::__path];
		}
		else
		{
			return __basic_elements[__value_element::__path].substr(0, end_path);
		}
	}

	std::string Parser::method()
	{
		if (__basic_elements[__value_element::__method].empty())
		{
			throw invalid_message;
		}
		else
		{
			return __basic_elements[__value_element::__method];
		}
	}

	std::string Parser::version()
	{
		if (__basic_elements[__value_element::__version].empty())
		{
			throw invalid_message;
		}
		else
		{
			return __basic_elements[__value_element::__version];
		}
	}

	std::string Parser::http_header(const std::string &name)
	{
		if (__http_headers.empty())
		{
			throw invalid_message;
		}

		for (std::vector<header>::iterator start = __http_headers.begin();
				start != __http_headers.end(); start++)
		{
			if (start->name == name)
			{
				return start->value;
			}
		}

		throw invalid_header_name;
	}

	std::string Parser::not_http_header(const std::string &name)
	{
		if (__not__http_headers.empty())
		{
			throw invalid_message;
		}

		for (std::vector<header>::iterator start = __not__http_headers.begin();
				start != __not__http_headers.end(); start++)
		{
			if (start->name == name)
			{
				return start->value;
			}
		}

		throw invalid_header_name;
	}

	
	Parser::~Parser() 
	{
	}
}
