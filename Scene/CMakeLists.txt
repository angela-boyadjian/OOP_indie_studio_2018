cmake_minimum_required(VERSION 3.13)
project(OOP_nanotekspice_2018)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(OOP_nanotekspice_2018
        srcs/main.cpp
        srcs/SceneManager.cpp srcs/SceneManager.hpp
        srcs/IScene.hpp
        srcs/MenuScene.cpp srcs/MenuScene.hpp)
