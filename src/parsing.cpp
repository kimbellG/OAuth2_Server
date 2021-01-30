#include "../include/parsing.hpp"

#include <iostream>
#include <cstring>

#include "../include/odebug.hpp"

namespace http
{
	Parser::Parser(std::string input)
	{
		std::size_t curr_pos = 0;

		__start_processing(input, curr_pos); 

		__headers_processing(input, curr_pos);

		__data__processing(input, curr_pos);
	
	}

	void Parser::__start_processing(const std::string &input, std::size_t &start_request)
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
				throw invalid_message;
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

	void Parser::__headers_processing(const std::string &input, std::size_t &start_headers)
	{
		std::size_t end_word;	
		std::string header_str;
		header tmp;
		end_word = input.find('\n', ++start_headers); 
	
		if (end_word == std::string::npos)
		{
			std::cerr << start_mes::start_err_mes << "Parser::__headers_processing()."
			   << "Not found: '\\n'" << std::endl;
			throw invalid_message;
		}
	
	
		while ((header_str = input.substr(start_headers, end_word - start_headers)) != "\r")
		{
			start_headers = end_word + 1;
			end_word = input.find('\n', start_headers);
			if (end_word == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::__headers_processing()."
				   << "Not found: '\\n'" << std::endl;
				throw invalid_message;
			}
			
	#ifdef DEBUG_HEADER
			std::cout << start_mes::debug_mes << header_str << std::endl;
	#endif //DEBUG_HEADER
	
			std::size_t value_start = header_str.find(':');
			if (value_start == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::__headers_processing. "
				   << "Not found: ':' in header's pars" << std::endl;
				throw invalid_message;
			}

			tmp.name = header_str.substr(0, value_start);
			tmp.value = header_str.substr(value_start + 2, header_str.size() - value_start);
	
			__headers.push_back(tmp);
		}
#ifdef DEBUG_HEADER
		for (std::size_t i = 0; i < __headers.size(); i++)
		{
			std::cout << start_mes::debug_mes 
				<< "HEADER.\tName = " << __headers[i].name << std::setw(10) 
				<< "\tValue = " << __headers[i].value << std::endl;
		}
#endif //DEBUG_HEADER
	}

	void Parser::__data__processing(const std::string &input, std::size_t &start_data)
	{
		start_data += 2;

		__data = input.substr(start_data, input.size() - start_data);

#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "DATA.\t" << __data << std::endl;
#endif //DEBUG_HEADER
	}

	std::string Parser::content_size()
	{
		for (std::size_t i = 0; i < __headers.size(); i++)
		{
			if (__headers[i].name == "Content-Length")
			{
				return __headers[i].value;
			}
		}
		throw empty_header;
	}

	std::string Parser::content_type()
	{
		for (std::size_t i = 0; i < __headers.size(); i++)
		{
			if (__headers[i].name == "Content-Type")
			{
				return __headers[i].value;
			}
		}
		throw empty_header;
	}

	std::string Parser::content_path()
	{
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
	
	Parser::~Parser() 
	{
	}
}
