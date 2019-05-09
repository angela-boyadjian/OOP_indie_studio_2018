cmake_minimum_required(VERSION 3.11)
project(OOP_indie_studio_2018)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lXxf86vm -lXext -lX11 -lGL -lGLU")

add_executable(bomberman
        Game/Characters/ACharacter.cpp
        Game/Display/Display.cpp
        irrlichtTest/test.cpp)

target_include_directories(bomberman PRIVATE
        LibIrrlicht/include/
        Game/Characters/
        Game/Display/
        Game/Events/
        Game/Logic/)

target_link_libraries(bomberman Irrlicht)