/**
 * @file VNode.cpp
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.13
 */

#include "../../Host.h"
#include <vector>
#include <boost/algorithm/string.hpp>
namespace gpds {


void NodePosition::add(const NodeId &key, std::shared_ptr<const RNode> node) {

}

void NodePosition::add(const std::vector<NodePair> &list) {
}

void NodePosition::ready() {
}

NodePair NodePosition::searchAfter(const NodeId key) {
	return (*m_nodes.begin());
}

NodePair NodePosition::searchBefore(const NodeId key) {
	return (*m_nodes.end());
}

void VNode::init(Host *host, uint8_t ringid, uint8_t nodeid[NODEID_LEN]){
}

bool VNode::interpret(std::shared_ptr<RNode> node, const h256 cnctid, uint8_t msgid, const uint8_t *data, uint16_t len) {
	return true;
}

void VNode::onconnected(std::shared_ptr<RNode> node) {
}


void VNode::procJoin(std::shared_ptr<RNode> node, const h256 cnctid, const uint8_t *data, uint16_t len) {
}

void VNode::procSendSuccessor(std::shared_ptr<RNode> node, const h256 cnctid, const uint8_t *data, uint16_t len) {
}

}

