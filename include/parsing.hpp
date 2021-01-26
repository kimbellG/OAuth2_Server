#ifndef __PARSING_HPP__
#define __PARSING_HPP__


#include <string>
#include <vector>
#include <boost/asio.hpp>

#define DEBUG_HEADER

struct header
{
	std::string name;
	std::string value;
};	

class Parser
{
	static const int __number_element = 3;
	enum
	{
		__method = 0,
		__path,
		__version
	} __value_element;
	std::string __basic_elements[__number_element];

	std::vector<header> __headers;
	
/*	void __start_processing();

	void __headers_processing(const std::size_t start_headers);
	void __req_processing();
*/
public:
	Parser(std::string input);
/*	
	std::string content_size();
	std::string content_type();
	std::string content_path();
	boost::asio::ip::tcp::endpoint &dest();

	std::string version();
	std::string answer();
*/
	~Parser();
};

#endif //__PARSING_HPP__
