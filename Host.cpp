/**
 * @file Host.cpp
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.13
 */

#include <chrono>
#include <boost/thread.hpp>
#include <string>
#include <vector>
#include <thread>
#include "Host.h"
#include "sha3.h"

namespace gpds {

struct MSG_HEADER {
	NETID		netid;
	h256		cnctid;
	uint8_t		ringid;
	uint8_t		msgid;
	uint8_t		len[2];
};

std::shared_ptr<Host> Host::m_host;

std::shared_ptr<Host> Host::getInstance() {
	if (m_host.use_count()==0) {
		m_host = std::shared_ptr<Host>(new Host());
		return std::move(m_host);
	}
	return m_host;
}

bool Host::run(NETID id, uint16_t port) {
	if (m_run) return false;
	m_run = true;
	m_acceptor = std::shared_ptr<bi::tcp::acceptor>(new bi::tcp::acceptor(m_io, bi::tcp::endpoint(bi::tcp::v4(), port)));
	std::memcpy(m_netid, id, 4);
	receive();
	boost::thread thd(boost::bind(&boost::asio::io_service::run, &m_io));
	return true;
}

void Host::receive() {
	auto socket = std::make_shared<bi::tcp::socket>(m_io);
	m_acceptor->async_accept(*socket, [=](const boost::system::error_code &ec) {
		if (ec.value()==boost::system::errc::success) {
			makeHostID(socket.get());
			auto ep = socket->local_endpoint();
			m_address = ep.address().to_string() + ":" + std::to_string(ep.port());
			std::cout << "accept:" << m_address << std::endl;
			auto node = std::make_shared<RNode>(this, socket);
			m_vecNode.push_back(node);
			node->receive(0, nullptr);
		} else {
			 std::cout << "Failed:async_accept:" + ec.message() << std::endl;
		}
		receive();
	});
}

void Host::makeHostID(const bi::tcp::socket *sock) {
	auto ep = sock->local_endpoint();
	auto adrs = ep.address().to_string(); 
	std::cout << "makeHostId:" << adrs << std::endl;
	H512(m_hostid, (const uint8_t *)adrs.c_str(), adrs.length());
	for ( int i=0; i<VNET_CNT; i++) {
		m_vnode[i].init(this, i, &m_hostid[i*NODEID_LEN]);
	}
}

bool Host::checkHostID(const h512 id, const std::string &ip) {
	h512 hostid;
	H512(m_hostid, (const uint8_t *)ip.c_str(), ip.length());
	return (std::memcmp(id, hostid, sizeof(h512))==0);
}

bool Host::checkNodeID(const NodeId nodeid, int ringid, const std::string &ip) {
	h512 hostid;
	H512(hostid, (const uint8_t *)ip.c_str(), ip.length());
	return (std::memcmp(nodeid, hostid+sizeof(NodeId)*ringid, sizeof(NodeId))==0);
	
}

bool Host::checkNetID(const NETID id )  {
	if (std::memcmp(id, m_netid, sizeof(NETID))!=0) {
		 std::cout << "invalid net id." << std::endl;
		return false;
	}
	return true;
}

bool Host::interpret(const RNode *node, const uint8_t *data, uint16_t len) {
	MSG_HEADER *head;
	head = (MSG_HEADER*)data;
	if (!checkNetID(head->netid)) {
		 std::cout << "invalid netid." << std::endl;
		return false;
	}
	uint16_t datalen = (uint16_t)b2l(head->len, sizeof(uint16_t));
	if (head->ringid>3) {
		 std::cout << "invalid ringid." << std::endl;
		return false;
	}
	std::cout << "receive::ringid:" << std::to_string(head->ringid) << " msgid:" << std::to_string(head->msgid) << " dataid:" << len;
	data += sizeof(MSG_HEADER);
	auto itr=m_vecNode.begin();
	for ( auto end=m_vecNode.end(); itr!=end; ++itr ) {
		if ((*itr).get()==node) {
			return m_vnode[head->ringid].interpret(*itr, head->cnctid, head->msgid, data, len);
		}
	}
	std::cout << "Host::interpret - can't find host" << std::endl;
	return false;
}


bool Host::cnct(std::string adrs, std::string port, std::function<void(std::shared_ptr<RNode>)> callback) {
	boost::system::error_code ec;
	bi::address addr = bi::address::from_string(adrs, ec);
	if (ec.value()==boost::system::errc::success) {
		bi::tcp::endpoint endpoint(addr, std::atoi(port.c_str()));
		auto socket = std::make_shared<bi::tcp::socket>(m_io);
		auto node = std::make_shared<RNode>(this, socket);
		socket->async_connect(endpoint, [=](const boost::system::error_code &ec) {
			if (ec.value()==boost::system::errc::success) {
				m_vecNode.push_back(node);
				if (!m_init) {
					m_init = true;
					makeHostID(socket.get());
					for ( int i=0; i<VNET_CNT; i++ ) {
						std::shared_ptr<std::function<void()>> callback;
						callback = std::make_shared<std::function<void()>>(
							[=]() {
								std::cout<<"lamda:::"<<std::endl;
								node->receive(2,callback);
							});
						node->receive(2, callback);
						m_vnode[i].onconnected(node);
						std::this_thread::sleep_for(std::chrono::seconds(1));
					}
				}
			} else {
				std::cout << "Host::cnct:" << ec.message() << std::endl;
			}
		});
		if (callback!=nullptr) {
			callback(node);
		}
	} else return false;
	boost::thread thd(boost::bind(&boost::asio::io_service::run, &m_io));
	return true;
}


bool Host::send(const RNode &node, const h256 cnctid, const uint8_t ringid, const uint8_t msgid, const uint8_t *data, const uint16_t len) {
	uint16_t totallen = sizeof(NETID)+sizeof(h256)+sizeof(uint32_t)+len;
	auto total = std::make_shared<std::vector<uint8_t>>();
	total->resize(totallen);
	MSG_HEADER *head = (MSG_HEADER*)total->data();
	std::memcpy(head->netid, m_netid, sizeof(NETID));
	std::memcpy(head->cnctid, cnctid, sizeof(h256));
	head->ringid = ringid;
	head->msgid = msgid;
	l2b(head->len, sizeof(uint16_t), len);
	if (len>0) {
		void *ptr = total->data() + sizeof(MSG_HEADER);
		std::memcpy(ptr, data, len);
		node.send(total, 0, nullptr);
	}
	return true;
}

void Host::makeCnctId(h256 &hash) {
	uint8_t *buff = new uint8_t[H512_LEN + sizeof(time_t)];
	std::memcpy(buff, m_hostid, H512_LEN);
	time_t tm = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::memcpy(buff+H512_LEN, &tm, sizeof(time_t));
	H256(hash, buff, H512_LEN + sizeof(time_t));
	delete[] buff;
}

} // namespace
