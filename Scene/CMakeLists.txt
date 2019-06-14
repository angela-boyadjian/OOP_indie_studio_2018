cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")

find_package(SFML 2.3 COMPONENTS audio REQUIRED)

include_directories(lib/irrLicht/include)

include_directories(
        srcs
)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/MenuScene.hpp srcs/MenuScene.cpp
        srcs/IScene.hpp
        srcs/SceneManager.hpp srcs/SceneManager.cpp
        srcs/GameScene.cpp srcs/GameScene.hpp
        srcs/SceneManagerException.cpp srcs/SceneManagerException.hpp
        srcs/SceneException.cpp srcs/SceneException.hpp)

target_link_libraries(${PROJECT_NAME} Irrlicht)
