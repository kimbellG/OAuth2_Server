#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "include/server.hpp"
#include "include/odebug.hpp"



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
				exit(1);
		}
	}

	boost::asio::io_context io;

	try
	{
		Server s(io, std::stoi(port));

		io.run();
	}
	catch (std::invalid_argument&)
	{
		std::cerr << start_mes::start_err_mes << "Invalid port" << std::endl;
		exit(1);
	}
	catch (std::out_of_range&) 
	{
		std::cerr << start_mes::start_err_mes << "Out of range" << std::endl;
		exit(1);
	}
	catch (std::exception &e)
	{
		std::cerr << start_mes::start_err_mes << "Expeption: " << e.what() << std::endl;
		exit(1);
	}

	return 0;

}
