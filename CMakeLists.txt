cmake_minimum_required(VERSION 3.18)
project(CloveceSEM)

set(CMAKE_CXX_STANDARD 14)

include_directories(CloveceSEM)

add_executable(CloveceSEM
        CloveceSEM/Figurka.cpp
        CloveceSEM/Figurka.h
        CloveceSEM/Hra.cpp
        CloveceSEM/Hra.h
        CloveceSEM/Hrac.cpp
        CloveceSEM/Hrac.h
        CloveceSEM/HraciaDoska.cpp
        CloveceSEM/HraciaDoska.h
        CloveceSEM/Kocka.h
        CloveceSEM/Main.cpp)
