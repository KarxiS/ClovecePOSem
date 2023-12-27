cmake_minimum_required(VERSION 3.18)
project(p14Wait)

set(CMAKE_CXX_STANDARD 17)

add_executable( p14Wait buffer.h main.c )

target_link_libraries(p14Wait wsock32 ws2_32)