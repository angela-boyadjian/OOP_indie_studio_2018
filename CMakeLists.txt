cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")
include_directories(lib/irrLicht/include)

include_directories(
        srcs/Map
        srcs/Logic
        srcs/Events
        srcs/Display
        srcs/Characters
        srcs/Objects
        srcs/Tool
        srcs/Core
        srcs/Menu
)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/Map/Map.cpp
        srcs/Map/Map.hpp
        srcs/Map/IMap.hpp
        srcs/Menu/IMenu.hpp
        srcs/Menu/Menu.cpp
        srcs/Menu/Menu.hpp
        srcs/Map/ATile.cpp
        srcs/Map/ATile.hpp
        srcs/Tool/Reader.cpp
        srcs/Tool/Reader.hpp
        srcs/Tool/SpriteInfo.hpp
        srcs/Map/MapData.hpp
        srcs/Logic/AGame.hpp
        srcs/Logic/BombermanGame.cpp
        srcs/Logic/BombermanGame.hpp
        srcs/Core/Bomberman.hpp
        srcs/Display/IDisplay.hpp
        srcs/Display/IDisplayLoader.hpp
        srcs/Core/Bomberman.cpp
        srcs/Characters/BombermanPlayers/Bot.cpp
        srcs/Display/IDisplay.hpp
        srcs/Characters/BombermanPlayers/ABombermanPlayer.cpp
        srcs/Characters/BombermanPlayers/Player.cpp
        srcs/Characters/BombermanPlayers/Player.hpp
        srcs/Characters/ACharacter.cpp
        srcs/Display/IDisplayLoader.hpp
        srcs/Display/IrrlichtDisplay.cpp
        srcs/Display/IrrlichtDisplay.hpp
        srcs/Display/IrrlichtDisplayLoader.hpp
        srcs/Display/IrrlichtDisplayLoader.cpp
        srcs/Objects/Bomb.cpp
        srcs/Objects/Bomb.hpp
)

target_link_libraries(${PROJECT_NAME} Irrlicht)
