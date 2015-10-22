#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <iostream>
#include <cstring>


int main() {
	boost::asio::io_service io;
	
	boost::asio::deadline_timer timer(io);
	timer.expires_from_now(boost::posix_time::seconds(3));
	timer.async_wait([&](const boost::system::error_code& error) {
		std::cout << "timer(" << error.message() << std::endl;
	});

	boost::asio::deadline_timer timer2(io);
	timer2.expires_from_now(boost::posix_time::seconds(4));
	timer2.async_wait([&](const boost::system::error_code& error) {
		std::cout << "timer2-1(" << error.message() << std::endl;
	});
	timer2.expires_from_now(boost::posix_time::seconds(5));
	timer2.async_wait([&](const boost::system::error_code& error) {
		std::cout << "timer2-2(" << error.message() << std::endl;
	});
	std::cout << "staart" << std::endl;
	io.run();
	std::cout << "end" << std::endl;
}
