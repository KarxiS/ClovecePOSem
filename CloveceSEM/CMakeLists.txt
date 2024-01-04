cmake_minimum_required(VERSION 3.18)

project(ClovecePOSem)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClovecePOSem
        Main.cpp
        Main.cpp
        HraciaDoska.cpp
        Hra.cpp
        Hrac.cpp
        HraciaDoska.cpp
        Figurka.cpp
        Policko.cpp
        Policko.h
        Policko.cpp)
find_package(Threads REQUIRED)
target_link_libraries(ClovecePOSem Threads::Threads)

