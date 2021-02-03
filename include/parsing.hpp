#ifndef __PARSING_HPP__
#define __PARSING_HPP__


#include <string>
#include <vector>
#include <boost/asio.hpp>

//#define DEBUG_HEADER
//#define DEBUG_TMP

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
		std::vector<header> __http_headers;
		std::string __data;
		std::vector<header> __not__http_headers;
		
		void  __start_processing(const std::string &input, int &start_request); // Заполенние метода, пути и версии запроса
	
		void __http_headers_processing(const std::string &input, int &start_headers) ; //Заполнение секции заголовков
		void __data__processing(const std::string &input, int &start_data); //Заполнение секции данных

		void __nhttp_headers_proccesing();
	
	public:
		enum exeptions
		{
			invalid_message,
			invalid_header_name
		};
		
		class invalid_message :
			public std::logic_error
		{
		public:
			invalid_message(std::string message)
				: std::logic_error(message)
			{
			}
		};

		class invalid_header_name :
			std::logic_error
		{
		public:
			invalid_header_name(std::string message)
				: std::logic_error(message)
			{
			}
		};

		
		Parser(std::string input);
	
		std::string path();
		std::string version();
		std::string method();
		std::string data();
	
		std::string http_header(const std::string &name);
		std::string not_http_header(const std::string &name);

		~Parser();
	};
};

#endif //__PARSING_HPP__
