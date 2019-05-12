cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
include_directories(lib/irrLicht/include)
include_directories(
        srcs/Game/Map
        srcs/Game/Display
        srcs/Game/Characters
        srcs/Game/Menu
        srcs/Core
)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/Game/Map/Map.cpp
        srcs/Game/Map/Map.hpp
        srcs/Game/Display/Display.cpp
        srcs/Game/Display/Display.hpp
        srcs/Game/Characters/ACharacter.cpp
        srcs/Game/Characters/ACharacter.hpp
        srcs/Game/Characters/Player.cpp
        srcs/Game/Characters/Player.hpp
        srcs/Core/Bomberman.cpp
        srcs/Core/Bomberman.hpp
        srcs/Game/Menu/Menu.cpp
        srcs/Game/Menu/Menu.hpp)

target_link_libraries(${PROJECT_NAME} Irrlicht)
