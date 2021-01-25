#include "../include/session.hpp"

#include <iostream>
#include <boost/bind/bind.hpp>

#include "../include/odebug.hpp"

void session::start()
{
#ifdef DEBUG
	std::cout << "[DEBUG] | Start session!" << std::endl;
	std::cout << start_mes::debug_mes << "Ip-address: " <<
	   	session::socket().remote_endpoint().address().to_string() << std::endl;
	std::cout << start_mes::debug_mes << "Port: " << socket().remote_endpoint().port() << std::endl;
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
		std::cout << "[DEBUG] | handshake is made" << std::endl;
#endif //DEBUG
		__socket.async_read_some(boost::asio::buffer(__inbuf, __szarr),
				boost::bind(&session::read_handle, this, 
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	} else
	{
		std::cerr << "[ERROR] | Session fault. session::handshake_handle()" << e.message() << std::endl;
		delete this;
	}
}

void session::read_handle(const boost::system::error_code &e, std::size_t bytes_transferred)
{
	if (!e)
	{
#ifdef DEBUG
		std::cout << start_mes::debug_mes << "Read data: " << std::endl;
		std::cout << '\t' << __inbuf << std::endl;
		std::cout << start_mes::debug_mes << "Write data: " << std::endl;
		std::cout << '\t' << __outbuf << std::endl;
#endif //DEBUG	
		boost::asio::async_write(__socket, boost::asio::buffer(__outbuf, bytes_transferred),
				boost::bind(&session::write_handle, this,
					boost::asio::placeholders::error));
	} else
	{
		std::cerr << start_mes::start_err_mes << "Session fault. session::read_handle: " 
			<< e.message() << std::endl;
		delete this;
	}	
}

void session::write_handle(const boost::system::error_code &e)
{
	if (!e)
	{
		__socket.async_read_some(boost::asio::buffer(__inbuf, __szarr),
				boost::bind(&session::read_handle, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	} else
	{
		std::cerr << start_mes::start_err_mes << "Session is fault. session::write_handle: "
			<< e.message() << std::endl;
	}
}


