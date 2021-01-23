#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>



int main(int argc, char *argv[])
{	
	std::string address;
	std::string port;

	int ret;
	while ((ret = ::getopt(argc, argv, "p:")) != -1)
	{
		switch (ret)
		{
			case 'p':
				port = ::optarg;
#ifdef DEBUG
				std::cout << "port: " << port << std::endl;
#endif // DEBUG
				break;
			case '?':
				std::cout << "Use server -p <port> " << std::endl;
				break;
		}
	}

	boost::asio::io_context io;
	boost::asio::ip::tcp::resolver resolver(io);


	return 0;

}
