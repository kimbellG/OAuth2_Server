#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "include/server.hpp"
#include "include/odebug.hpp"

namespace http
{
	std::string root_path;
}


int main(int argc, char *argv[])
{	
	std::string port;

	int ret;
	while ((ret = ::getopt(argc, argv, "p:d:")) != -1)
	{
		switch (ret)
		{
			case 'p':
				port = ::optarg;
#ifdef DEBUG
				std::cout << "port: " << port << std::endl;
#endif // DEBUG
				break;
			case 'd':
				http::root_path = ::optarg;
#ifdef DEBUG
				std::cout << "root path: " << http::root_path << std::endl;
#endif //DEBUG
				break;

			case '?':
				std::cout << "Use server -p <port> -d <root_path> " << std::endl;
				exit(1);
		}
	}

	if (port.empty() || http::root_path.empty())
	{
		std::cerr << "Invalid argument. " << std::endl;
		std::cerr << "Usage server -p <port> -d <root_path>" << std::endl;
		exit(1);
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
