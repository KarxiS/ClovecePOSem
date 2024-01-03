cmake_minimum_required(VERSION 3.18)

project(ClovecePOSem)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClovecePOSem
        CloveceSEM/Main.cpp
        CloveceSEM/Main.cpp
        CloveceSEM/HraciaDoska.cpp
        CloveceSEM/Hra.cpp
        CloveceSEM/Hrac.cpp
        CloveceSEM/HraciaDoska.cpp
        CloveceSEM/Figurka.cpp
        CloveceSEM/Policko.cpp
        CloveceSEM/Policko.h
        CloveceSEM/Policko.cpp)
find_package(Threads REQUIRED)
target_link_libraries(ClovecePOSem Threads::Threads)

