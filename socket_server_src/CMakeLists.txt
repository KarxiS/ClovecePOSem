cmake_minimum_required(VERSION 3.18)
project(socket_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(socket_server main.cpp)

target_link_libraries(socket_server pthread)