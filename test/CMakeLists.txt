cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

find_path(
	LEVELDB_INCLUDE_DIR 
	NAMES leveldb/db.h
	DOC "leveldb include dir"
)

find_library(
	LEVELDB_LIBRARY
	NAMES leveldb
	DOC "leveldb library"
)


# use multithreaded boost libraries, with -mt suffix
set(Boost_USE_MULTITHREADED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

# TODO hanlde other msvc versions or it will fail find them
	set(Boost_COMPILER -vc120)
# use static boost libraries *.lib
	set(Boost_USE_STATIC_LIBS ON) 

elseif (APPLE)

# use static boost libraries *.a
	set(Boost_USE_STATIC_LIBS ON) 

elseif (UNIX)
# use dynamic boost libraries .dll
	set(Boost_USE_STATIC_LIBS OFF) 

endif()

find_package(Boost 1.54.0 REQUIRED COMPONENTS thread date_time system regex chrono filesystem unit_test_framework program_options)

message(" - boost header: ${Boost_INCLUDE_DIRS}")
message(" - boost lib   : ${Boost_LIBRARIES}")

if (APPLE)
	link_directories(/usr/local/lib)
	include_directories(/usr/local/include)
	set(CMAKE_CXX_FLAGS "-m64 -O0 -std=c++11 -stdlib=libc++ -g")
	set(DCMAKE_CXX_COMPILER "clang++")
elseif(UNIX)
	link_directories(/usr/lib)
	include_directories(/usr/include)
	set(CMAKE_CXX_FLAGS "-m64 -O0 -std=c++11 -g")
	set(DCMAKE_CXX_COMPILER "clang++")
endif()

add_executable(testapp test.cpp socket/aaa.cpp) 
#add_library(gpds Host.cpp Peer.cpp DHTHost.cpp)
set(CMAKE_BUILD_TYPE Debug)
target_link_libraries(testapp ${LEVELDB_LIBRARY} ${Boost_LIBRARIES})

add_executable(runapp run.cpp)
target_link_libraries(runapp ${LEVELDB_LIBRARY} ${Boost_LIBRARIES} ${CMAKE_BINARY_DIR}/../../build/libgpds.a)


#add_executable(accpapp accept.cpp)
#target_link_libraries(accpapp ${LEVELDB_LIBRARY} ${Boost_LIBRARIES})

#add_executable(cnntapp connect.cpp)
#target_link_libraries(cnntapp ${LEVELDB_LIBRARY} ${Boost_LIBRARIES})
