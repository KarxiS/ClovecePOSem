cmake_minimum_required(VERSION 3.18)
project(socket_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(socket_server main.cpp

        ../CloveceSEM/Figurka.cpp
        ../CloveceSEM/Figurka.h
        ../CloveceSEM/Hra.cpp
        ../CloveceSEM/Hra.h
        ../CloveceSEM/Hrac.cpp
        ../CloveceSEM/Hrac.h
        ../CloveceSEM/HraciaDoska.cpp
        ../CloveceSEM/HraciaDoska.h
        ../CloveceSEM/Kocka.h

        ../CloveceSEM/Policko.cpp
        ../CloveceSEM/Policko.h
)

target_link_libraries(socket_server pthread)