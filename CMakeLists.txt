cmake_minimum_required(VERSION 3.8)
# プロジェクト名を指定する
project(robot_system VERSION 1.0.0)
add_executable(${CMAKE_PROJECT_NAME} Example/robot_system.cpp Comm/comm_udp.cpp)

if(WIN32)
	target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)
endif()
