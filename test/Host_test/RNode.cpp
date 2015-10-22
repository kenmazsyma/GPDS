/**
 * @file RNode.cpp
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.14
 */
#include "../../Host.h"

namespace gpds {


void RNode::receive(int timeout, std::shared_ptr<std::function<void()>> callback) const {
}


void RNode::send(std::shared_ptr<std::vector<uint8_t>> data, int timeout, std::function<void()> callback) const {
}

std::shared_ptr<std::string> RNode::getAddress() {
	return nullptr;
}


std::string RNode::getLocalEndPoint() {
	return "";
}

std::string RNode::getRemoteEndPoint() {
	return "";
}


} // namespace
