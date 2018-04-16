cmake_minimum_required(VERSION 3.10)

project(reduction)
option(ENABLE_TESTS "Enables building test projects [default: ON]" ON)

add_subdirectory(library)
add_subdirectory(cli)

if(ENABLE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()