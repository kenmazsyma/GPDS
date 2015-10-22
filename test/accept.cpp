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
	
	m_acceptor = std::shared_ptr<boost::asio::ip::tcp::acceptor>(new boost::asio::ip::tcp::acceptor(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 15945)));
	auto socket = std::make_shared<boost::asio::ip::tcp::socket>(m_io);

	m_acceptor->async_accept(*socket, [=](const boost::system::error_code &ec) {
		cout << ec.message();
		auto b = make_shared<boost::array<char,100>>();
		boost::asio::async_read(*socket, boost::asio::buffer(*b), [=](const boost::system::error_code &ec, std::size_t len ) {
			cout << ec.message();
			boost::asio::async_write(*socket, boost::asio::buffer(*b), [=](const boost::system::error_code &ec, std::size_t size) {
				cout << ec.message();
			});
		});
	});
	m_io.run();
	while(1) {
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
