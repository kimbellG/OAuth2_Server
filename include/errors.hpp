#ifndef __ERRORS_TYPE_HPP__
#define __ERRORS_TYPE_HPP__

#include <iostream>
#include <vector>
#include <memory>

#include "parsing.hpp"

namespace http
{
	namespace error
	{
		class Error
		{
			std::string __code;
			std::string __err_message;
			std::shared_ptr<std::vector<header>> __http_headers;
			std::string __filename;

		public:
			Error(const std::string& code, const std::string &err_message, const std::string& filename);

			void add_header(const std::string &name, const std::string &value);	
			
			virtual std::unique_ptr<std::string> get_answer() const;

			virtual ~Error() = 0;
		};

		class BadRequest : public Error
		{
		public:
			BadRequest();

			std::unique_ptr<std::string> get_answer() const;

			~BadRequest();
		};

		class Forbidden : public Error
		{
		public:
			Forbidden();

			std::unique_ptr<std::string> get_answer() const;

			~Forbidden();
		};

		class NotFound : public Error
		{
		public:
			NotFound();

			std::unique_ptr<std::string> get_answer() const;

			~NotFound();
		};

		class MethodNotAllowed : public Error
		{
		public:
			MethodNotAllowed();

			std::unique_ptr<std::string> get_answer() const;

			~MethodNotAllowed();
		};

		class LengthRequired : public Error
		{
		public:
			LengthRequired();

			std::unique_ptr<std::string> get_answer() const;

			~LengthRequired();
		};

		class NotImplemented : public Error
		{
		public:
			NotImplemented();

			std::unique_ptr<std::string> get_answer() const;

			~NotImplemented();
		};

		class HTTPVersionNotSupported : public Error
		{
		public:
			HTTPVersionNotSupported();

			std::unique_ptr<std::string> get_answer() const;

			~HTTPVersionNotSupported();
		};

	}
}



#endif //__ERRORS_TYPE_HPP__
