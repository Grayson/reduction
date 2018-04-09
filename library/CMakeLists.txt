cmake_minimum_required(VERSION 3.10)

project(libreduction)

set(PUBLIC_HEADERS
	include/reduction/reduction.hpp)

add_library(libreduction
	${PUBLIC_HEADERS}
	src/reduction.cpp)

target_include_directories(libreduction
	INTERFACE include
	PRIVATE include/reduction src)

install(
	TARGETS libreduction
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)

set_target_properties(libreduction PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "reduction")