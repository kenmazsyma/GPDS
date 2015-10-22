/**
 * @file RNode.h
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.14
 */

#include "Common.h"
#include <functional>

namespace gpds {

class Host;

class RNode {
public:
	enum CONNECT_STATE { NO_CONNECTED, WAIT_RECEIVE, CONNECTED };
	RNode(Host *host, std::shared_ptr<bi::tcp::socket> socket) 
		: m_host(host), m_socket(socket) {};
	
	void receive( int timeout, std::shared_ptr<std::function<void()>> callback) const;
	void send(std::shared_ptr<std::vector<uint8_t>> data, int timeout, std::function<void()> callback) const;
	
	std::shared_ptr<std::string> getAddress();

	std::string getLocalEndPoint();
	std::string getRemoteEndPoint();

private:
	Host *m_host;
	std::shared_ptr<bi::tcp::socket> m_socket;
};

} // namespace
