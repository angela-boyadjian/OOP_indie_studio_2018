cmake_minimum_required(VERSION 3.11)
project(OOP_indie_studio_2018)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lXxf86vm -lXext -lX11 -lGL -lGLU")

include_directories(LibIrrlicht/include/
        Game/Characters/ACharacter.hpp
        Game/Characters/Player.hpp
        Game/Characters/Bot.hpp)

add_executable(OOP_indie_studio_2018
        Game/Characters/ACharacter.cpp
        irrlichtTest/test.cpp)

target_link_libraries(OOP_indie_studio_2018 Irrlicht)