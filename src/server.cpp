#include "../include/server.hpp"

#include <iostream>
#include <boost/bind/bind.hpp>

#include "../include/odebug.hpp"

Server::Server(boost::asio::io_context &io, unsigned int port) :
	__io(io),
	__acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	__ssl_context(boost::asio::ssl::context::sslv23)
{
	__ssl_context.set_options(
			boost::asio::ssl::context::default_workarounds
			| boost::asio::ssl::context::no_sslv2
			| boost::asio::ssl::context::single_dh_use);
	__ssl_context.use_certificate_chain_file("/etc/letsencrypt/live/pcalice.ddns.net/fullchain.pem");
	__ssl_context.use_private_key_file("/etc/letsencrypt/live/pcalice.ddns.net/privkey.pem",
			boost::asio::ssl::context::pem);
	
	start_accept();
}

std::string Server::get_password() const
{
	return "test";
}

void Server::start_accept()
{
	session *new_ses = new session(__io, __ssl_context);
	__acceptor.async_accept(new_ses->socket(),
			boost::bind(&Server::handle_accept, this, new_ses,
				boost::asio::placeholders::error));
}

void Server::handle_accept(session *new_session, const boost::system::error_code &e) 
{
	if (!e)
	{
		new_session->start();
	} else
	{
		std::cerr << start_mes::start_err_mes << "Accept fault. Server::handle_accept: " <<
			e.message() << std::endl;
		delete new_session;
	}

	start_accept();
}



