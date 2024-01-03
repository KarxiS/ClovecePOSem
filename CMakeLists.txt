cmake_minimum_required(VERSION 3.18)

project(ClovecePOSem)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClovecePOSem
        CloveceSEMFix/Main.cpp
        CloveceSEMFix/Main.cpp
        CloveceSEMFix/HraciaDoska.cpp
        CloveceSEMFix/Hra.cpp
        CloveceSEMFix/Hrac.cpp
        CloveceSEMFix/HraciaDoska.cpp
        CloveceSEMFix/Figurka.cpp
        CloveceSEMFix/Policko.cpp
        CloveceSEMFix/Policko.h
        CloveceSEMFix/Policko.cpp)
find_package(Threads REQUIRED)
target_link_libraries(ClovecePOSem Threads::Threads)

