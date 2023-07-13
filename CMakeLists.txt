cmake_minimum_required(VERSION 3.8)
# プロジェクト名を指定する
project(utils_udp VERSION 1.0.0)
add_executable(${CMAKE_PROJECT_NAME} Example/example_udp.cpp Comm/comm_udp.cpp)

if(WIN32)
	target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)
endif()
