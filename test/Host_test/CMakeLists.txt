cmake_minimum_required(VERSION 2.8)

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
add_definitions( -DSOCKET_UT )
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
	include_directories(/usr/include /usr/include/c++/4.8 /usr/include/x86_64-linux-gnu/c++/4.8)
	set(CMAKE_CXX_FLAGS "-m64 -O0 -std=c++11 -g")
	set(CMAKE_C_FLAGS "-m64 -O0 -std=gnu99 -g")
	set(DCMAKE_CXX_COMPILER "clang++")
endif()

message("GTEST_DIR : $ENV{GTEST_DIR}")

include_directories(%ENV{GTEST_DIR}/include)
#AUX_SOURCE_DIRECTORY($ENV{GTEST_DIR}/include/gtest GTEST_HEADER1)
#AUX_SOURCE_DIRECTORY($ENV{GTEST_DIR}/include/gtest/internal GTEST_HEADER2)
add_executable(Host_test ${CMAKE_BINARY_DIR}/../../socket/tcp.cpp test.cpp VNode.cpp RNode.cpp ${CMAKE_BINARY_DIR}/../../../sha3.c ${CMAKE_BINARY_DIR}/../../../Host.cpp)
set(CMAKE_BUILD_TYPE Debug)
target_link_libraries(Host_test pthread ${Boost_LIBRARIES})
#target_link_libraries(Host_test pthread $ENV{GTEST_DIR}/build/libgtest_main.a $ENV{GTEST_DIR}/build/libgtest.a )
