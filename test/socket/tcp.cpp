#include "tcp.hpp"

namespace boost {
namespace asio {
namespace ip {
	tcp::socket *tcp::m_sock = nullptr;
	callback tcp::m_cb;
}
}
}
