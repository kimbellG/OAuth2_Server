#include "../include/parsing.hpp"

#include <iostream>
#include <cstring>

#include "../include/odebug.hpp"

namespace http
{
	Parser::Parser(std::string input)
	{
		std::size_t curr_pos = 0;
		std::size_t end_word;
		for (int i = 0; i < __value_element::__number_elements; i++)
		{
			end_word = input.find((i == __version) ? '\r' : ' ', curr_pos);

			if (end_word == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::Parser. Invalid message from client."
					<< "Not found - ' ', '\\r'" << std::endl;
				throw invalid_message;
			}

			__basic_elements[i] = input.substr(curr_pos, end_word - curr_pos);
			curr_pos = end_word + 1;
		}
	#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "Method: " << __basic_elements[__method] << std::endl;
		std::cout << start_mes::debug_mes << "Path: " << __basic_elements[__path] << std::endl;
		std::cout << start_mes::debug_mes << "Version: " << __basic_elements[__version] << std::endl;
	#endif //DEBUG
	
		std::string header_str;
		header tmp;
		end_word = input.find('\n', ++curr_pos); 
	
		if (end_word == std::string::npos)
		{
			std::cerr << start_mes::start_err_mes << "Parser::Parser. Not found: '\\n'" << std::endl;
			throw invalid_message;
		}
	
	
		while ((header_str = input.substr(curr_pos, end_word - curr_pos)) != "\r")
		{
			curr_pos = end_word + 1;
			end_word = input.find('\n', curr_pos);
			if (end_word == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::Parser. Not found: '\\n'" << std::endl;
				throw invalid_message;
			}
			
	#ifdef DEBUG_HEADER
			std::cout << start_mes::debug_mes << header_str << std::endl;
	#endif //DEBUG_HEADER
	
			std::size_t value_start = header_str.find(':');
			if (value_start == std::string::npos)
			{
				std::cerr << start_mes::start_err_mes << "Parser::Parser. Not found: ':' in header's pars"
					<< std::endl;
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

		curr_pos += 2;
		__data = input.substr(curr_pos, input.size() - curr_pos);

#ifdef DEBUG_HEADER
		std::cout << start_mes::debug_mes << "DATA.\t" << __data << std::endl;
#endif //DEBUG_HEADER

	}
	
	Parser::~Parser() {
	}
}
