cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

include_directories(lib/irrLicht/include)
include_directories(
        srcs/Map
        srcs/Menu
        srcs/Tool
        srcs/Core
        srcs/Logic
        srcs/Events
        srcs/Display
        srcs/Characters
)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/Map/Map.cpp
        srcs/Map/IMap.hpp
        srcs/Menu/IMenu.hpp
        srcs/Menu/Menu.cpp
        srcs/Map/ATile.cpp
        srcs/Tool/Reader.cpp
        srcs/Tool/Reader.hpp
        srcs/Map/MapData.hpp
        srcs/Logic/AGame.hpp
        srcs/Core/Bomberman.hpp
        srcs/Characters/Bot.cpp
        srcs/Tool/SpriteInfo.hpp
        srcs/Display/IDisplay.hpp
        srcs/Characters/Player.cpp
        srcs/Logic/BombermanGame.cpp
        srcs/Characters/ACharacter.cpp
        srcs/Display/IDisplayLoader.hpp
        srcs/Display/IrrlichtDisplay.cpp
        srcs/Display/IrrlichtDisplayLoader.hpp
        srcs/Game/SceneManager/SceneManager.cpp
        srcs/Game/SceneManager/SceneManager.hpp
)

target_link_libraries(${PROJECT_NAME} Irrlicht)