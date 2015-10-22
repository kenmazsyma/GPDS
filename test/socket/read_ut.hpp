/**
 * @file : read_ut.hpp
 * @author : Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date : 2015
 * @desciption : a stub of boost::asio::acceptor for unit testing
 */

#ifndef BOOST_ASIO_READ_HPP
#define BOOST_ASIO_READ_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

//#include <boost/asio/detail/config.hpp>
//#include <cstddef>
//#include <boost/asio/async_result.hpp>
//#include <boost/asio/basic_streambuf_fwd.hpp>
//#include <boost/asio/error.hpp>
//
//#include <boost/asio/detail/push_options.hpp>

using namespace std;

namespace boost {
namespace asio {

template <typename SyncReadStream, typename MutableBufferSequence>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncReadStream, typename MutableBufferSequence>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncReadStream, typename MutableBufferSequence,
  typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncReadStream, typename Allocator>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncReadStream, typename Allocator>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b,
    boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncReadStream, typename Allocator,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncReadStream, typename Allocator,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncReadStream, typename MutableBufferSequence,
    typename ReadHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {
}

template <typename AsyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition, typename ReadHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {
}

#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

}

template <typename AsyncReadStream, typename Allocator,
    typename CompletionCondition, typename ReadHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

/*@}*/

} // namespace asio
} // namespace boost

//#include <boost/asio/detail/pop_options.hpp>

//#include <boost/asio/impl/read.hpp>

#endif // BOOST_ASIO_READ_HPP
