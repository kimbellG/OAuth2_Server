#ifndef __ERRORS_TYPE_HPP__
#define __ERRORS_TYPE_HPP__

#include <iostream>
#include <vector>
#include <memory>

#include "parsing.hpp"
#include"reply.hpp"

namespace http
{
	namespace error
	{
		class Error
		{
			Answer __answer;

		public:
			Error(const std::string& code, const std::string &err_message, const std::string& filename);

			std::unique_ptr<std::string> get_answer() const;
			
			virtual ~Error() = 0;
		};

		class BadRequest : public Error
		{
		public:
			BadRequest();
			~BadRequest();
		};

		class Forbidden : public Error
		{
		public:
			Forbidden();
			~Forbidden();
		};

		class NotFound : public Error
		{
		public:
			NotFound();
			~NotFound();
		};

		class MethodNotAllowed : public Error
		{
		public:
			MethodNotAllowed();
			~MethodNotAllowed();
		};

		class LengthRequired : public Error
		{
		public:
			LengthRequired();
			~LengthRequired();
		};

		class NotImplemented : public Error
		{
		public:
			NotImplemented();
			~NotImplemented();
		};

		class HTTPVersionNotSupported : public Error
		{
		public:
			HTTPVersionNotSupported();
			~HTTPVersionNotSupported();
		};

	}
}



#endif //__ERRORS_TYPE_HPP__
