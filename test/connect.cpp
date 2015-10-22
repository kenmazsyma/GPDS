#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <vector>
#include <iostream>
#include <cstring>
#include <thread>

using namespace std;

int main() {
	std::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
	boost::asio::io_service m_io;
	
	boost::asio::ip::address addr = boost::asio::ip::address::from_string("192.168.56.100");
	boost::asio::ip::tcp::endpoint endpoint(addr, 15945);
	auto socket = make_shared<boost::asio::ip::tcp::socket>(m_io);
	socket->async_connect(endpoint, [=](const boost::system::error_code &ec) {
		auto b = make_shared<boost::array<char,100>>();
		boost::asio::async_write(*socket, boost::asio::buffer(*b), [=](const boost::system::error_code &ec, std::size_t size) {
			boost::asio::async_read(*socket, boost::asio::buffer(*b), [=](const boost::system::error_code &ec, std::size_t len ) {
				cout << ec.message();
			});
		});
	});
	m_io.run();
	while(1) {
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

