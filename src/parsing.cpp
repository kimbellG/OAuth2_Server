#include "../include/parsing.hpp"

#include <iostream>
#include <cstring>

#include "../include/odebug.hpp"

Parser::Parser(std::string input)
{
	int curr_pos = 0;
	int end_word;
	for (int i = 0; i < __number_element; i++)
	{
		end_word = input.find(' ', curr_pos);
		input.substr(curr_pos, end_word);
		curr_pos += end_word + 1;
	}
#ifdef DEBUG
	std::cout << start_mes::debug_mes << "Method: " << __basic_elements[__method] << std::endl;
	std::cout << start_mes::debug_mes << "Path: " << __basic_elements[__path] << std::endl;
	std::cout << start_mes::debug_mes << "Version: " << __basic_elements[__version] << std::endl;
#endif //DEBUG

	__headers = new header[30];

	__start_processing();
}

Parser::~Parser()
{
	delete[] __headers;
}
