#ifndef __PARSING_HPP__
#define __PARSING_HPP__


#include <string>
#include <vector>
#include <boost/asio.hpp>

#define DEBUG_HEADER

namespace http
{
	
	struct header
	{
		std::string name;
		std::string value;
	};	
	
	class Parser
	{
		enum __value_element
		{
			__method = 0,
			__path,
			__version,
			__number_elements
		};
		
		std::string __basic_elements[__value_element::__number_elements];
		std::vector<header> __headers;
		std::string __data;
		
		void  __start_processing(std::size_t &start_request); // Заполенние метода, пути и версии запроса
	
		void __headers_processing(std::size_t &start_headers) ; //Заполнение секции заголовков
		void __data__processing(std::size_t &start_data); //Заполнение секции данных
	
	public:
		enum exeptions
		{
			invalid_message
		};
		
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
};

#endif //__PARSING_HPP__
