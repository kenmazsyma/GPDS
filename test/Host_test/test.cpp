#include <gtest/gtest.h>
#include "../../Host.h"

using namespace gpds;



int main(int argc, char **argv) {

	std::shared_ptr<Host> host = Host::getInstance();
	NETID id;
	std::function<void(const boost::system::error_code &)> callback = nullptr;
	try {
		host->run(id, 10000);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
//	if (boost::asio::ip::tcp::m_cb==nullptr) {
		boost::system::error_code ec;
		//boost::asio::ip::tcp::m_sock->;
		boost::asio::ip::tcp::m_cb(ec);
//	}
}



