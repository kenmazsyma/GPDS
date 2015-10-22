/**
 * @file VNode.cpp
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.13
 */

#include "Host.h"
#include <vector>
#include <boost/algorithm/string.hpp>
namespace gpds {

struct FIND_SUCCESSOR_DATA{
	NodeId id;
	const char address[30];
};

void NodePosition::add(const NodeId &key, std::shared_ptr<const RNode> node) {
	auto pair = std::make_shared<std::pair<NodeId, std::shared_ptr<const RNode>>>();
	std::memcpy(pair->first, key, sizeof(NodeId));
	pair->second = node;
	m_nodes.push_back(pair);
}

void NodePosition::add(const std::vector<NodePair> &list) {
	if (list.size()==0) return;
	m_nodes.insert(m_nodes.end(), list.begin(), list.end());
}

void NodePosition::ready() {
	std::sort(m_nodes.begin(), m_nodes.end(), [=](const NodePair &c1, const NodePair &c2) {
		return c1 > c2;
	});
}

NodePair NodePosition::searchAfter(const NodeId key) {
	for ( auto itr=m_nodes.begin(), end=m_nodes.end(); itr!=end; ++itr ) {
		if (std::memcmp(key, (*itr)->first, sizeof(NodeId)) < 0 ) return (*itr);
	}
	return (*m_nodes.begin());
}

NodePair NodePosition::searchBefore(const NodeId key) {
	for ( auto itr=m_nodes.begin(), end=m_nodes.end(); itr!=end; ++itr ) {
		if (std::memcmp(key, (*itr)->first, sizeof(NodeId)) < 0 ) return (*--itr);
	}
	return (*m_nodes.end());
}

void VNode::init(Host *host, uint8_t ringid, uint8_t nodeid[NODEID_LEN]){
	m_host = host;
	m_ringid = ringid;
	std::memcpy(m_nodeid, nodeid, NODEID_LEN);
}

bool VNode::interpret(std::shared_ptr<RNode> node, const h256 cnctid, uint8_t msgid, const uint8_t *data, uint16_t len) {
	switch (msgid) {
	case JOIN:
		procJoin(node, cnctid, data, len);
		break;
	case SEND_SUCCESSOR:
		procSendSuccessor(node, cnctid, data, len);
	}
	return true;
}

void VNode::onconnected(std::shared_ptr<RNode> node) {
	if (m_host==nullptr) return;
	h256 cnctid;
	m_host->makeCnctId(cnctid);
	auto wait = std::make_shared<std::pair<h256, std::shared_ptr<RNode>>>();
	std::memcpy(wait->first, cnctid, sizeof(h256));
	wait->second = nullptr;
	m_waitres.push_back(wait);
	m_host->send(*(node.get()), cnctid, m_ringid, JOIN, m_nodeid, NODEID_LEN);
}


void VNode::procJoin(std::shared_ptr<RNode> node, const h256 cnctid, const uint8_t *data, uint16_t len) {
	std::cout << "JOIN" << std::endl;
	NodePosition np;
	NodeId *recvid = *((NodeId**)&data);
	std::shared_ptr<std::string> rip = node->getAddress();
	std::cout<<rip<<std::endl;
	if (!m_host->checkNodeID(*recvid, m_ringid, *rip)) {
		std::cout << "JOIN:Invalid NodeId" << std::endl;
		return;
	}
	np.add(m_nodeid, nullptr);
	np.add(m_suclist);
	np.ready();
	NodePair pair = np.searchAfter(*recvid);
	if (pair->second==nullptr) {
		const std::string address = m_host->getAddress();
		std::vector<uint8_t> buf;
		uint16_t len;
		len = sizeof(NodeId) + address.size() +1;
		buf.resize(len);
		std::memcpy(buf.data(), m_nodeid, sizeof(NodeId));
		std::memcpy(buf.data()+sizeof(NodeId), address.c_str(), address.size());
		buf[len-1] = 0x0;
		m_host->send(*node.get(), cnctid, m_ringid, SEND_SUCCESSOR, buf.data(),len);
	} else {
		auto wait = std::make_shared<std::pair<h256, std::shared_ptr<RNode>>>();
		memcpy(wait->first, cnctid, sizeof(h256));
		wait->second = node;
		m_waitres.push_back(wait);
		m_host->send(*pair->second, cnctid, m_ringid, JOIN, data, len);
	}
}

void VNode::procSendSuccessor(std::shared_ptr<RNode> node, const h256 cnctid, const uint8_t *data, uint16_t len) {
	std::cout << "SEND_SUCCESSOR" << std::endl;
	for ( auto itr=m_waitres.begin(), end=m_waitres.end(); itr!=end; ++itr) {
		if (std::memcmp(cnctid, (*itr)->first, sizeof(h256))==0) {
			if ((*itr)->second==nullptr) {
				std::cout << "FOUND:SUCCESSOR" << std::endl;
				FIND_SUCCESSOR_DATA *buf;
				buf = (FIND_SUCCESSOR_DATA*)data;
				std::vector<char> address;
				address.resize(len);
				std::memcpy(address.data(), buf->address, len-sizeof(NodeId));
				int portpos = 0;
				for ( ;portpos<len; portpos++) {
					if (address[portpos]==':') {
						address[portpos++] = 0x0;
						break;
					}
				}
				m_host->cnct(address.data(), address.data()+portpos, [=](std::shared_ptr<RNode> node) {
					auto pair = std::make_shared<std::pair<NodeId, std::shared_ptr<const RNode>>>();
					std::memcpy((void*)pair->first, buf->id, sizeof(NodeId));
					pair->second = node;
					m_suclist.push_back(pair);
				});
			} else {
				m_host->send(*(*itr)->second, cnctid, m_ringid, SEND_SUCCESSOR, data, len);
			}
			return;
		}
	}

	std::cout << "VNode::procSendSuccessor - can't find join message" << std::endl;
}


}

