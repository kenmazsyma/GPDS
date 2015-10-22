/**
 * @file Host.h
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.13
 */
#include "VNode.h"

namespace gpds {

class Host {
public:
	static std::shared_ptr<Host> getInstance();
	bool run(NETID id, uint16_t port);
	bool cnct(std::string adrs, std::string port, std::function<void(std::shared_ptr<RNode>)>);
	bool interpret(const RNode *node, const uint8_t *data, uint16_t len);
	bool send(const RNode &node, const h256 cnctId, const uint8_t ringId, const uint8_t msgId, const uint8_t *data, const uint16_t len);
	void makeCnctId(h256 &hash);
	inline const std::string &getAddress() { return m_address; }
	bool checkNodeID(const NodeId nodeid, int ringid, const std::string &ip);
	inline boost::asio::io_service *getIO() { return &m_io; };
private:
	static std::shared_ptr<Host> m_host;
	Host():m_run(false), m_init(false) {};
	void receive();
	bool checkNetID(const NETID id );
	void makeHostID(const bi::tcp::socket *sock);
	bool checkHostID(const h512 id, const std::string &ip);

	NETID m_netid;
	h512 m_hostid;
	bool m_run;
	bool m_init;
	std::shared_ptr<bi::tcp::acceptor> m_acceptor;
	std::vector<std::shared_ptr<RNode>> m_vecNode;
	boost::asio::io_service m_io;
	std::string m_address;

	VNode m_vnode[VNET_CNT];

};

} // namespace
