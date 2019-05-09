cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

include_directories(LibIrrlicht/include)
include_directories(srcs/Game/Map)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/Game/Map/Map.cpp
        srcs/Game/Map/Map.hpp
)

target_link_libraries(${PROJECT_NAME} Irrlicht)
