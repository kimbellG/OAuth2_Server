#ifndef __SESSION_HPP__
#define __SESSION_HPP__


#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_sock;

class session
{
	ssl_sock __socket;
	
	static const int __szarr = 4096;
	unsigned char __inbuf[__szarr];	
	unsigned char __outbuf[__szarr];

public:
	session(boost::asio::io_context &io, boost::asio::ssl::context &ssl_io) :
		__socket(io, ssl_io)
	{
	}

	ssl_sock::lowest_layer_type& socket()
	{
		return __socket.lowest_layer();
	}

	void start();
	
	void handshake_handle(const boost::system::error_code &e);
	void read_handle(const boost::system::error_code &e, std::size_t bytes_transferred);
	void write_handle(const boost::system::error_code &e);
};


#endif // __SESSION_HPP__
