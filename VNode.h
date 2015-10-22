/**
 * @file VNode.h
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.4.13
 */

#include "RNode.h"
#include <unordered_map>
#include <utility>

namespace gpds {

#define NODEID_LEN (sizeof(h512)/VNET_CNT)
using NodeId=uint8_t[NODEID_LEN];
using NodeKey=MemWrap<NodeId>;
using key256=MemWrap<h256>;

enum MSGCODE{
	JOIN,
	SEND_SUCCESSOR
};

using NodePair=std::shared_ptr<std::pair<NodeId, std::shared_ptr<const RNode>>>;

class NodePosition {
public:
	void add(const NodeId &key, std::shared_ptr<const RNode> node);
	void add(const std::vector<NodePair> &list);
	void ready();
	NodePair searchAfter(const NodeId key);
	NodePair searchBefore(const NodeId key);
private:
	std::vector<NodePair> m_nodes;
};

class Host;
class VNode {
public:
	VNode():m_host(nullptr){};
	void init(Host *host, uint8_t ringid, uint8_t nodeid[NODEID_LEN]);
	bool interpret(std::shared_ptr<RNode> node, const h256 cnctid, uint8_t msgid, const uint8_t *data, uint16_t len);
	void onconnected(std::shared_ptr<RNode> node);

private:

	NodeId  m_nodeid;
	uint8_t m_ringid;
	Host *m_host;
	std::vector<std::shared_ptr<std::pair<h256, std::shared_ptr<RNode>>>> m_waitres;
	std::vector<NodePair> m_suclist;

	void procJoin(std::shared_ptr<RNode> node, const h256 cnctid, const uint8_t *data, uint16_t len);
	void procSendSuccessor(std::shared_ptr<RNode> node, const h256 cnctid, const uint8_t *data, uint16_t len);
};

}
