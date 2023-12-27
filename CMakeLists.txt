cmake_minimum_required(VERSION 3.18)
project(ClovecePOSem)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClovecePOSem main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(ClovecePOSem Threads::Threads)