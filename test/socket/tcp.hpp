
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/buffer.hpp>

namespace boost {
namespace asio {

#ifndef BOOST_ASIO_IP_TCP_HPP
#define BOOST_ASIO_IP_TCP_HPP
	
	
namespace ip {
	typedef std::function<void(const boost::system::error_code &)> callback;

class tcp {
public: 

	//typedef basic_stream_socket<tcp> socket;
	//typedef basic_endpoint<tcp> endpoint;
	class endpoint {
	public:
	  endpoint(const tcp& internet_protocol,
	      unsigned short port_num)
	  {
	  }
	
	  endpoint(const boost::asio::ip::address& addr, unsigned short port_num)
	  {
	  }

	  endpoint() 
	  {
	  }
	  
	  unsigned short port() const
	  {
	    return 80;
	  }
	
	  void port(unsigned short port_num)
	  {
	  }
	
	  boost::asio::ip::address address() const
	  {
		boost::asio::ip::address address;
	    return address;
	  }
	
	  void address(const boost::asio::ip::address& addr)
	  {
	  }
	
	
	};
  /// The TCP resolver type.
  typedef basic_resolver<tcp> resolver;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  /// The TCP iostream type.
  typedef basic_socket_iostream<tcp> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

	static callback m_cb;

	class socket {
	public:
  		explicit socket(boost::asio::io_service& io_service)
  		{
  		}
  		endpoint local_endpoint() const {
			endpoint e;
			return e;
		}
		void async_connect(const endpoint& peer_endpoint,
		    BOOST_ASIO_MOVE_ARG(callback) handler)
		{
		}
	};

	class acceptor {
	public:
		acceptor(boost::asio::io_service& io_service,
		    const tcp& protocol)
		{
		}
	
		acceptor(boost::asio::io_service& io_service,
		    const endpoint& endpoint, bool reuse_addr = true)
		{
		}
	
		void async_accept(socket &sock, callback &&cb) {
			m_sock = &sock;
			m_cb = std::move(cb);
		};
	};
  /// Construct to represent the IPv4 TCP protocol.
  static tcp v4()
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 TCP protocol.
  static tcp v6()
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const
  {
    return BOOST_ASIO_OS_DEF(SOCK_STREAM);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const
  {
    return BOOST_ASIO_OS_DEF(IPPROTO_TCP);
  }

  /// Obtain an identifier for the protocol family.
  int family() const
  {
    return family_;
  }
	static socket *m_sock;
private:
  // Construct with a specific family.
  explicit tcp(int protocol_family)
    : family_(protocol_family)
  {
  }

  int family_;
};

}

#endif // BOOST_ASIO_IP_TCP_HPP

#ifndef BOOST_ASIO_WRITE_HPP
#define BOOST_ASIO_WRITE_HPP

typedef std::function<void(const boost::system::error_code &, std::size_t)> callback2;

void async_write(boost::asio::ip::tcp::socket& s, const boost::asio::buffer& buffers,
    callback2 &&handler) {

}


//void async_write(boost::asio::ip::tcp::socket& s, const boost::asio::buffer& buffers,
//    CompletionCondition completion_condition,
//    callback2 &&handler);


//void async_write(boost::asio::ip::tcp::socket& s, basic_streambuf<Allocator>& b,
//    CompletionCondition completion_condition,
//    callback2 &&handler);

#endif // BOOST_ASIO_WRITE_HPP


#ifndef BOOST_ASIO_READ_HPP
#define BOOST_ASIO_READ_HPP

typedef std::function<void(const boost::system::error_code &, std::size_t)> callback3;


void async_read(boost::asio::ip::tcp::socket& s, const boost::asio::buffer& buffers,
    callback3 &&handler);


//void async_read(boost::asio::ip::tcp::socket& s, const boost::asio::buffer& buffers,
//    CompletionCondition completion_condition,
//    callback2 &&handler);

#endif // BOOST_ASIO_READ_HPP

}
}


