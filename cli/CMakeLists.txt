cmake_minimum_required(VERSION 3.10)

project(cli)

add_executable(cli
	src/main.cpp)
	
target_link_libraries(cli PRIVATE libreduction)
	
install(TARGETS cli	DESTINATION bin)

set_target_properties(cli PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "reduction")
