cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

project(libreduction)

ExternalProject_Add(deduction
	PREFIX ${CMAKE_BINARY_DIR}/deduction
	GIT_REPOSITORY git@github.com:Grayson/deduction.git
	GIT_TAG 3c6db33077fe5c54835e8ec4363bad8023ad9c2f
	GIT_SHALLOW YES
	CMAKE_ARGS -DDATATYPES_ONLY=ON -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
set(DEDUCTION_INCLUDE_DIR "${CMAKE_BINARY_DIR}/deduction/include")
set(DEDUCTION_JSON_LIB "${CMAKE_BINARY_DIR}/deduction/lib/libdeduction-datatypes-json.a")

ExternalProject_Add(fmtlib
	PREFIX ${CMAKE_BINARY_DIR}/fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt
	GIT_TAG 4.1.0
	GIT_SHALLOW YES
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
set(FMT_INCLUDE_DIR "${CMAKE_BINARY_DIR}/fmt/include")
set(FMT_LIB "${CMAKE_BINARY_DIR}/fmt/lib/libfmt.a")
	
add_library(libreduction
	include/reduction/name_mangler.hpp
	include/reduction/reduction.hpp
	src/bridge.hpp
	src/name_mangler.cpp
	src/utility.hpp
	src/utility.cpp)

add_dependencies(libreduction deduction fmtlib)

target_link_libraries(libreduction PRIVATE ${DEDUCTION_JSON_LIB} ${FMT_LIB})

target_include_directories(libreduction
	INTERFACE include
	PRIVATE include/reduction src ${DEDUCTION_INCLUDE_DIR} ${FMT_INCLUDE_DIR})

install(
	TARGETS libreduction
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)

set_target_properties(libreduction PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "reduction")