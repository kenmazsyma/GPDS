/**
 * @file : basic_socket_acceptor_ut.hpp
 * @author : Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date : 2015
 * @desciption : a stub of boost::asio::acceptor for unit testing
 */

#ifndef BOOST_ASIO_WRITE_HPP
#define BOOST_ASIO_WRITE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/asio/error.hpp>
//
//#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename SyncWriteStream, typename ConstBufferSequence>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncWriteStream, typename ConstBufferSequence>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncWriteStream, typename Allocator>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncWriteStream, typename Allocator>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b,
    boost::system::error_code& ec) {
	// TODO:NOT IMPLEMENT!!
	return 0;
}

template <typename SyncWriteStream, typename Allocator,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition){
	// TODO:NOT IMPLEMENT!!
	return 0;
}



template <typename SyncWriteStream, typename Allocator,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec){
	// TODO:NOT IMPLEMENT!!
	return 0;
}


#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncWriteStream, typename ConstBufferSequence,
    typename WriteHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler);

template <typename AsyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition, typename WriteHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler);

#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncWriteStream, typename Allocator, typename WriteHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler);

template <typename AsyncWriteStream, typename Allocator,
    typename CompletionCondition, typename WriteHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace asio
} // namespace boost

//#include <boost/asio/detail/pop_options.hpp>

//#include <boost/asio/impl/write.hpp>

#endif // BOOST_ASIO_WRITE_HPP
