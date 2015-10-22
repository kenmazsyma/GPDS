#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <iostream>
#include <cstring>
#include <thread>
#include <boost/algorithm/string/predicate.hpp>
#include "../Host.h"


int main(int argc, char** argv)
{
	std::shared_ptr<gpds::Host> host = gpds::Host::getInstance();
	gpds::NETID id;
	id[0] = 0x50;
	id[1] = 0x51;
	id[2] = 0x52;
	id[3] = 0x54;
	host->run(id, 15945);

/*	bool exit = false;
	std::string l;
	while(!exit) {
		std::getline(std::cin, l);
		if (l.length()==0) continue;
		std::stringstream iss(l);
		std::string cmd;
		iss >> cmd;
		if (cmd=="exit") {
			exit = true;
		}
		if (boost::algorithm::starts_with(cmd, "peer")) {
			std::vector<std::string> v;
			boost::algorithm::split(v, cmd, boost::algorithm::is_any_of(":") );
			if (v.size() != 3 ) {
				std::cout << "usage: peer ip port";
			} else {
				host->cnct(v[1], v[2], nullptr);
			}
		} else {
			std::cout << "no peer";
		}
	}*/
}
