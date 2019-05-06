cmake_minimum_required(VERSION 3.14)
project(OOP_indie_studio_2018)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lXxf86vm -lXext -lX11 -lGL -lGLU -lIrrlicht")

add_library(libIrrlicht SHARED IMPORTED)

include_directories(LibIrrlicht/include/)

add_executable(OOP_indie_studio_2018
        irrlichtTest/test.cpp)

