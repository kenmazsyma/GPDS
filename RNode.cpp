/**
 * @file RNode.cpp
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.14
 */
#include "Host.h"
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <cstring>
#include <iostream>
#include <mutex>

namespace gpds {

std::mutex mtx;

void RNode::receive(int timeout, std::shared_ptr<std::function<void()>> callback) const {
	auto b = std::make_shared<boost::array<uint8_t,65535>>();
	bool received = false;
	auto timer = std::make_shared<boost::asio::deadline_timer>(*m_host->getIO());
	std::cout << "RNode::receive:" << m_socket.use_count() << std::endl;
	async_read(*m_socket, boost::asio::buffer(*b), boost::asio::transfer_at_least(sizeof(NETID)+sizeof(uint32_t)),
	[&, timer, b](const boost::system::error_code &ec, size_t l) {
		received = true;
		std::lock_guard<std::mutex> lock(mtx);
		std::cout << "RNode::received::timer:" << timer.use_count() << std::endl;
		if (ec.value()!=boost::system::errc::success) {
			std::cout << "Failed::RNode::receive1:" + ec.message() << std::endl;
			mtx.unlock();
			return;
		}
		std::cout << "receiving size:" << l << std::endl;
		const uint8_t *d = b->data();
		receive(0, nullptr);
		m_host->interpret(this, d, l);
	});
	if (timeout>0 && callback!=nullptr) {
		timer->expires_from_now(boost::posix_time::seconds(timeout));
		timer->async_wait([=, &received](const boost::system::error_code& error) {
			if (received) return;
			std::lock_guard<std::mutex> lock(mtx);
			(*callback)();
			m_socket->cancel();
		});
	}
}


void RNode::send(std::shared_ptr<std::vector<uint8_t>> data, int timeout, std::function<void()> callback) const {
	int size = data->size();
	bool sent = false;
	std::cout << " Node::send(P):" << m_socket.use_count() << std::endl;
	async_write(*m_socket, boost::asio::buffer(*data.get(), size),
	[&](const boost::system::error_code &ec, std::size_t size) {
		std::lock_guard<std::mutex> lock(mtx);
		sent = true;
		if (ec.value()==boost::system::errc::success) {
			std::cout << "Succeed:send:" << size << std::endl;
		} else {
			std::cout << " Node::send:" + ec.message() << std::endl;
		}
	});
	if (timeout>0 && callback!=nullptr) {
		boost::asio::deadline_timer timer(*m_host->getIO());
		timer.expires_from_now(boost::posix_time::seconds(timeout));
		timer.async_wait([&](const boost::system::error_code& error) {
			if (!sent) {
				callback();
			}
		});
	}
}

std::shared_ptr<std::string> RNode::getAddress() {
	if (m_socket.use_count()==0) return std::make_shared<std::string>();
	return std::make_shared<std::string>(m_socket->remote_endpoint().address().to_string());
}


std::string RNode::getLocalEndPoint() {
	bi::tcp::endpoint ep = m_socket.get()->local_endpoint();
	return ep.address().to_string() + ":" + std::to_string(ep.port());
}

std::string RNode::getRemoteEndPoint() {
	bi::tcp::endpoint ep = m_socket.get()->remote_endpoint();
	return ep.address().to_string() + ":" + std::to_string(ep.port());
}


} // namespace
