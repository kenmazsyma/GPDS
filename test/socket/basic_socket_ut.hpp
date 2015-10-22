/**
 * @file : basic_socket_ut.hpp
 * @author : Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date : 2015
 * @desciption : a stub of boost::asio::socket for unit testing
 */

#ifndef BOOST_ASIO_BASIC_SOCKET_HPP
#define BOOST_ASIO_BASIC_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

//#include <boost/asio/detail/config.hpp>
//#include <boost/asio/async_result.hpp>
//#include <boost/asio/basic_io_object.hpp>
//#include <boost/asio/detail/handler_type_requirements.hpp>
//#include <boost/asio/detail/throw_error.hpp>
//#include <boost/asio/detail/type_traits.hpp>
//#include <boost/asio/error.hpp>
//#include <boost/asio/socket_base.hpp>
//
//#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename Protocol, typename SocketService>
class basic_socket
  : public basic_io_object<SocketService>,
    public socket_base
{
public:
  typedef typename SocketService::native_handle_type native_type;

  typedef typename SocketService::native_handle_type native_handle_type;

  typedef Protocol protocol_type;

  typedef typename Protocol::endpoint endpoint_type;

  typedef basic_socket<Protocol, SocketService> lowest_layer_type;

  explicit basic_socket(boost::asio::io_service& io_service)
    : basic_io_object<SocketService>(io_service)
  {
  }

  basic_socket(boost::asio::io_service& io_service,
      const protocol_type& protocol)
    : basic_io_object<SocketService>(io_service)
  {
  }

  basic_socket(boost::asio::io_service& io_service,
      const endpoint_type& endpoint)
    : basic_io_object<SocketService>(io_service)
  {
  }

  basic_socket(boost::asio::io_service& io_service,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_io_object<SocketService>(io_service)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  basic_socket(basic_socket&& other)
    : basic_io_object<SocketService>(
        BOOST_ASIO_MOVE_CAST(basic_socket)(other))
  {
  }

  basic_socket& operator=(basic_socket&& other)
  {
    return *this;
  }

  template <typename Protocol1, typename SocketService1>
  friend class basic_socket;

  template <typename Protocol1, typename SocketService1>
  basic_socket(basic_socket<Protocol1, SocketService1>&& other,
      typename enable_if<is_convertible<Protocol1, Protocol>::value>::type* = 0)
    : basic_io_object<SocketService>(other.get_io_service())
  {
  }

  template <typename Protocol1, typename SocketService1>
  typename enable_if<is_convertible<Protocol1, Protocol>::value,
      basic_socket>::type& operator=(
        basic_socket<Protocol1, SocketService1>&& other)
  {
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  lowest_layer_type& lowest_layer()
  {
    return *this;
  }

  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  void open(const protocol_type& protocol = protocol_type())
  {
  }

  boost::system::error_code open(const protocol_type& protocol,
      boost::system::error_code& ec)
  {
	  boost::syste::error_code er;
    return er;
  }

  void assign(const protocol_type& protocol,
      const native_handle_type& native_socket)
  {
  }

  boost::system::error_code assign(const protocol_type& protocol,
      const native_handle_type& native_socket, boost::system::error_code& ec)
  {
    boost::syste::error_code er;
    return er;
  }

  bool is_open() const
  {
    return true;
  }

  void close()
  {
  }

  boost::system::error_code close(boost::system::error_code& ec)
  {
    boost::syste::error_code er;
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

#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600) \
  && !defined(BOOST_ASIO_ENABLE_CANCELIO)
  __declspec(deprecated("By default, this function always fails with "
        "operation_not_supported when used on Windows XP, Windows Server 2003, "
        "or earlier. Consult documentation for details."))
#endif
  void cancel()
  {
  }

#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600) \
  && !defined(BOOST_ASIO_ENABLE_CANCELIO)
  __declspec(deprecated("By default, this function always fails with "
        "operation_not_supported when used on Windows XP, Windows Server 2003, "
        "or earlier. Consult documentation for details."))
#endif
  boost::system::error_code cancel(boost::system::error_code& ec)
  {
    boost::syste::error_code er;
    return er;
  }

  bool at_mark() const
  {
	return true;
  }

  bool at_mark(boost::system::error_code& ec) const
  {
	return true;
  }

  std::size_t available() const
  {
	return 0;
  }

  std::size_t available(boost::system::error_code& ec) const
  {
    return 0;
  }

  void bind(const endpoint_type& endpoint)
  {
  }

  boost::system::error_code bind(const endpoint_type& endpoint,
      boost::system::error_code& ec)
  {
    boost::syste::error_code er;
    return er;
  }

  void connect(const endpoint_type& peer_endpoint)
  {
  }

  boost::system::error_code connect(const endpoint_type& peer_endpoint,
      boost::system::error_code& ec)
  {
    boost::syste::error_code er;
    return er;
  }

  template <typename ConnectHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(ConnectHandler,
      void (boost::system::error_code))
  async_connect(const endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(ConnectHandler) handler)
  {

  template <typename SettableSocketOption>
  void set_option(const SettableSocketOption& option)
  {
  }

  template <typename SettableSocketOption>
  boost::system::error_code set_option(const SettableSocketOption& option,
      boost::system::error_code& ec)
  {
    boost::syste::error_code er;
    return er;
  }

  template <typename GettableSocketOption>
  void get_option(GettableSocketOption& option) const
  {
  }

  template <typename GettableSocketOption>
  boost::system::error_code get_option(GettableSocketOption& option,
      boost::system::error_code& ec) const
  {
    boost::syste::error_code er;
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
    boost::syste::error_code er;
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
    boost::syste::error_code er;
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
    boost::syste::error_code er;
    return er;
  }

  endpoint_type m_local_endpoint;

  endpoint_type local_endpoint() const
  {
    return m_local_endpoint;
  }

  endpoint_type local_endpoint(boost::system::error_code& ec) const
  {
    return m_local_endpoint;
  }

  endpoint_type m_remote_endpoint;

  endpoint_type remote_endpoint() const
  {
    return m_remote_endpoint;
  }

  endpoint_type remote_endpoint(boost::system::error_code& ec) const
  {
    return m_remote_endpoint;
  }
  void shutdown(shutdown_type what)
  {
  }

  boost::system::error_code shutdown(shutdown_type what,
      boost::system::error_code& ec)
  {
    boost::syste::error_code er;
    return er;
  }

protected:
  ~basic_socket()
  {
  }
};

} // namespace asio
} // namespace boost

// #include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SOCKET_HPP
