/**
 * @file Common.h
 * @author Ken.Matsushima <ken.ma24ma@yahoo.com>
 * @date 2015.3.20
 */

#ifdef SOCKET_UT
//#include "test/socket/basic_socket_acceptor_ut.hpp"
//#include "test/socket/basic_socket_ut.hpp"
//#include "test/socket/read_ut.hpp"
//#include "test/socket/write_ut.hpp"
#include "test/socket/tcp.hpp"
#endif

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <iostream>

namespace gpds {

using NETID = uint8_t[4];

namespace bi = boost::asio::ip;

#define VNET_CNT (4)

#define H256_LEN 32
#define H512_LEN 64

#define H256 SHA3_256
#define H512 SHA3_512

using h256 = uint8_t[H256_LEN];
using h512 = uint8_t[H512_LEN];

template<typename T1>
struct MemWrap {
	T1 key;
	
	MemWrap(const T1 &val) { std::memcpy(key, val, sizeof(T1)); }

	inline bool operator >(const MemWrap &tgt) const {
		return std::memcmp(key,tgt.key,sizeof(T1)) > 0;
	}
	
	inline bool operator <(const MemWrap &tgt) const {
		return std::memcmp(key,tgt.key, sizeof(T1)) < 0;
	}
	
	inline bool operator >=(const MemWrap &tgt) const {
		return std::memcmp(key,tgt.key,sizeof(T1)) >= 0;
	}
	
	inline bool operator <=(const MemWrap &tgt) const {
		return std::memcmp(key,tgt.key, sizeof(T1)) <= 0;
	}
	
	inline bool operator ==(const MemWrap &tgt) const {
		return std::memcmp(key,tgt.key, sizeof(T1)) == 0;
	}
	
};


inline long b2l( const uint8_t *data, long l) {
	long ret = 0;
	if (l<=sizeof(long)) for (int i=0; i<l; i++) ret = (ret<<8) + data[i];
	return ret;
}

inline void l2b ( uint8_t *out, long l, long d) {
	while(l--) {
		out[l] = d&0xff; 
		d=d>>8;
	}
}

} // namespace
