#ifndef __SERVER_HPP__
#define __SERVER_HPP__


#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "session.hpp"

class Server
{
	boost::asio::io_context &__io;
	boost::asio::ip::tcp::acceptor __acceptor;
	boost::asio::ssl::context __ssl_context;

public:
	Server(boost::asio::io_context &io, unsigned int port);

	void start_accept();
	
	std::string get_password() const;
	void handle_accept(const boost::system::error_code &e);
};

#endif //__SERVER_HPP__
