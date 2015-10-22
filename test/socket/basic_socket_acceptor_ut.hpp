/**
 * @file : basic_socket_acceptor_ut.hpp
 * @author : Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date : 2015
 * @desciption : a stub of boost::asio::acceptor for unit testing
 */


#ifndef BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_HPP
#define BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_HPP
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
//#include <boost/asio/detail/config.hpp>
//#include <boost/asio/basic_io_object.hpp>
//#include <boost/asio/basic_socket.hpp>
//#include <boost/asio/detail/handler_type_requirements.hpp>
//#include <boost/asio/detail/throw_error.hpp>
//#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/socket_acceptor_service.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
//#include <boost/asio/detailptions.hpp>
#include <iostream>

namespace boost {
namespace asio {

template <typename Protocol, /*typename SocketService,*/ typename AcceptHandler>
class AcceptData {
public:
	AcceptData() {
	}
	typename Protocol::endpoint endpoint_type;
	
	typedef std::function<void(
       basic_stream_socket<Protocol>&,
       ip::basic_endpoint<Protocol>&, 
	   BOOST_ASIO_MOVE_ARG(AcceptHandler)
	)> acceptcallback;

	static acceptcallback &&m_cb;
	static int aaaa;
	static void setCallback(
		acceptcallback &&callback
	) {
		m_cb = static_cast<acceptcallback&&>(callback);
		aaaa = 10;
	}

	static void getCallback( acceptcallback &&cb ) {
		cb = std::move(m_cb);
		std::cout << aaaa << std::endl;
	}

};
//template <typename Protocol, /*typename SocketService,*/ typename AcceptHandler>
//int AcceptData<Protocol, AcceptHandler>::aaaa = 3;

//template <typename Protocol, /*typename SocketService,*/ typename AcceptHandler>
//typename AcceptData<Protocol, AcceptHandler>::acceptcallback &&AcceptData<Protocol, AcceptHandler>::m_cb = nullptr;//AcceptData<Protocol, AcceptHandler>::acceptcallback();

template <typename Protocol,
    typename SocketAcceptorService = socket_acceptor_service<Protocol> >
class basic_socket_acceptor
  : public basic_io_object<SocketAcceptorService>,
    public socket_base
{
public:
  typedef typename SocketAcceptorService::native_handle_type native_type;

  typedef typename SocketAcceptorService::native_handle_type native_handle_type;

  typedef Protocol protocol_type;

  typedef typename Protocol::endpoint endpoint_type;

  explicit basic_socket_acceptor(boost::asio::io_service& io_service)
    : basic_io_object<SocketAcceptorService>(io_service)
  {
  }

  basic_socket_acceptor(boost::asio::io_service& io_service,
      const protocol_type& protocol)
    : basic_io_object<SocketAcceptorService>(io_service)
  {
  }

  basic_socket_acceptor(boost::asio::io_service& io_service,
      const endpoint_type& endpoint, bool reuse_addr = true)
    : basic_io_object<SocketAcceptorService>(io_service)
  {
  }

  basic_socket_acceptor(boost::asio::io_service& io_service,
      const protocol_type& protocol, const native_handle_type& native_acceptor)
    : basic_io_object<SocketAcceptorService>(io_service)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  basic_socket_acceptor(basic_socket_acceptor&& other)
    : basic_io_object<SocketAcceptorService>(
        BOOST_ASIO_MOVE_CAST(basic_socket_acceptor)(other))
  {
  }

  basic_socket_acceptor& operator=(basic_socket_acceptor&& other)
  {
    return *this;
  }

  template <typename Protocol1, typename SocketAcceptorService1>
  friend class basic_socket_acceptor;

  template <typename Protocol1, typename SocketAcceptorService1>
  basic_socket_acceptor(
      basic_socket_acceptor<Protocol1, SocketAcceptorService1>&& other,
      typename enable_if<is_convertible<Protocol1, Protocol>::value>::type* = 0)
    : basic_io_object<SocketAcceptorService>(other.get_io_service())
  {
  }

  template <typename Protocol1, typename SocketAcceptorService1>
  typename enable_if<is_convertible<Protocol1, Protocol>::value,
      basic_socket_acceptor>::type& operator=(
        basic_socket_acceptor<Protocol1, SocketAcceptorService1>&& other)
  {
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  void open(const protocol_type& protocol = protocol_type())
  {
  }

  boost::system::error_code open(const protocol_type& protocol,
      boost::system::error_code& ec)
  {
  }

  void assign(const protocol_type& protocol,
      const native_handle_type& native_acceptor)
  {
  }

  boost::system::error_code assign(const protocol_type& protocol,
      const native_handle_type& native_acceptor, boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  bool is_open() const
  {
    return true;
  }

  void bind(const endpoint_type& endpoint)
  {
  }

  boost::system::error_code bind(const endpoint_type& endpoint,
      boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  void listen(int backlog = socket_base::max_connections)
  {
  }

  boost::system::error_code listen(int backlog, boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  void close()
  {
  }

  boost::system::error_code close(boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }


  native_type native()
  {
    return this->get_service().native_handle(this->get_implementation());
  }

  native_handle_type native_handle()
  {
    return this->get_service().native_handle(this->get_implementation());
  }

  void cancel()
  {
  }

  boost::system::error_code cancel(boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }
  
  template <typename SettableSocketOption>
  void set_option(const SettableSocketOption& option)
  {
  }

  template <typename SettableSocketOption>
  boost::system::error_code set_option(const SettableSocketOption& option,
      boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  template <typename GettableSocketOption>
  void get_option(GettableSocketOption& option)
  {
  }

  template <typename GettableSocketOption>
  boost::system::error_code get_option(GettableSocketOption& option,
      boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  template <typename IoControlCommand>
  void io_control(IoControlCommand& command)
  {
  }

  template <typename IoControlCommand>
  boost::system::error_code io_control(IoControlCommand& command,
      boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  bool non_blocking() const
  {
	return true;
  }

  void non_blocking(bool mode)
  {
  }

  boost::system::error_code non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  bool native_non_blocking() const
  {
	return true;
  }

  void native_non_blocking(bool mode)
  {
  }

  boost::system::error_code native_non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  endpoint_type local_endpoint() const
  {
    endpoint_type ep;
    return ep;
  }

  endpoint_type local_endpoint(boost::system::error_code& ec) const
  {
    endpoint_type ep;
    return ep;
  }

  template <typename Protocol1, typename SocketService>
  void accept(basic_socket<Protocol1, SocketService>& peer,
      typename enable_if<is_convertible<Protocol, Protocol1>::value>::type* = 0)
  {
  }

  template <typename Protocol1, typename SocketService>
  boost::system::error_code accept(
      basic_socket<Protocol1, SocketService>& peer,
      boost::system::error_code& ec,
      typename enable_if<is_convertible<Protocol, Protocol1>::value>::type* = 0)
  {
    boost::system::error_code er;
    return er;
  }
  // vv TEST CODE vv
//  static std::function<void(boost::asio::socket_base&,
//		  std::function<void(const boost::system::error_code&)>&&)> m_handler;
//  static void setAcceptCallback(std::function<void(boost::asio::socket_base& peer,
//		  std::function<void(const boost::system::error_code&)>&&)> &&handler ) {
//    m_handler = handler;
//  }
//
  //static std::function<void( AcceptData<Protocol, SocketService, AcceptHandler>&&)> acceptevent;
  //static void setAcceptCallback(std::function<void()> &&event) {
	//	acceptevent = event;
  //}


  // ^^ TEST CODE ^^

  template <typename Protocol1, typename SocketService, typename AcceptHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(AcceptHandler,
      void (boost::system::error_code))
  async_accept(basic_socket<Protocol1, SocketService>& peer,
      BOOST_ASIO_MOVE_ARG(AcceptHandler) handler,
      typename enable_if<is_convertible<Protocol, Protocol1>::value>::type* = 0){

	 typedef typename AcceptData<Protocol1, AcceptHandler>::acceptcallback acb;
	 acb cb;
	 endpoint_type peer_endpoint{};
	 AcceptData<Protocol1, AcceptHandler>::getCallback(static_cast<acb&&>(cb));
	 cb(static_cast<basic_stream_socket<Protocol1>&>(peer), peer_endpoint, static_cast<AcceptHandler&&>(handler));
	  // m_handler(peer, std::move(handler));
	//  AcceptData<Protocol, SocketService, AcceptHandler> data(std::move(handler));
	//  data.peer = &peer;
	//  acceptevent(std::move(data));
  }


  template <typename socketservice>
  void accept(basic_socket<protocol_type, socketservice>& peer,
      endpoint_type& peer_endpoint)
  {
  }

  template <typename SocketService>
  boost::system::error_code accept(
      basic_socket<protocol_type, SocketService>& peer,
      endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    boost::system::error_code er;
    return er;
  }

  template <typename SocketService, typename AcceptHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(AcceptHandler,
      void (boost::system::error_code))
  async_accept(basic_socket<protocol_type, SocketService>& peer,
      endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler)
  {
  }
};
//template <typename Protocol,
//    typename SocketAcceptorService>
//std::function<void()> basic_socket_acceptor<Protocol, SocketAcceptorService>::acceptevent;
//template <typename Protocol,
//    typename SocketAcceptorService>
//std::function<void(boost::asio::socket_base&,
//		std::function<void(const boost::system::error_code &)>&&)> basic_socket_acceptor<Protocol, SocketAcceptorService>::m_handler;
//
//template <typename Protocol,
//    typename socketacceptorservice>
//boost::asio::socket_base *basic_socket_acceptor<Protocol, SocketAcceptorService>::socket = nullptr;

} // namespace asio
} // namespace boost

//#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_HPP
