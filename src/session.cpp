#include "../include/session.hpp"

#include <iostream>
#include <boost/bind/bind.hpp>

void session::start()
{
#ifdef DEBUG
	std::cout << "[DEBUG] | Start session!" << std::endl;
#endif //DEBUG

	__socket.async_handshake(boost::asio::ssl::stream_base::server, 
			boost::bind(&session::handshake_handle, this,
				boost::asio::placeholders::error));
}

void session::handshake_handle(const boost::system::error_code &e)
{
	if (!e)
	{
#ifdef DEBUG
		std::cout << "[DEBUG] | handshake is made" >> std::endl;
#endif //DEBUG
		__socket.async_read_some(boost::asio::buffer(__buf, __szarr),
				boost::bind(&session::read_handle, this, 
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	} else
	{
		std::cerr << "[ERROR] | Session fault. session::handshake_handle()" << std::endl;
		delete this;
	}
}


