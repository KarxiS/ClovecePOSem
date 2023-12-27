cmake_minimum_required(VERSION 3.18)
project(p14Wait)

set(CMAKE_CXX_STANDARD 17)

add_executable( p14Wait my_socket.h main.cpp my_socket.cpp)

target_link_libraries(p14Wait wsock32 ws2_32)