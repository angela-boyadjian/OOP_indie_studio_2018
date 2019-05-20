cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

include_directories(lib/irrLicht/include)
include_directories(
        srcs/Game/Map
        srcs/Game/Logic
        srcs/Game/Events
        srcs/Game/Display
        srcs/Game/Characters
        srcs/Game/Menu
        srcs/Game/Tool
        srcs/Core
)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/Game/Map/Map.cpp
        srcs/Game/Map/Map.hpp
        srcs/Game/Map/IMap.hpp
        srcs/Game/Map/ATile.cpp
        srcs/Game/Map/ATile.hpp
        srcs/Core/Bomberman.hpp
        srcs/Game/Menu/IMenu.hpp
        srcs/Game/Menu/Menu.cpp
        srcs/Game/Menu/Menu.hpp
        srcs/Core/Bomberman.cpp
        srcs/Game/Logic/BombermanGame.cpp
        srcs/Game/Tool/Reader.cpp
        srcs/Game/Tool/Reader.hpp
        srcs/Game/Map/MapData.hpp
        srcs/Game/Logic/AGame.hpp
        srcs/Game/Characters/Bot.cpp
        srcs/Game/Characters/Bot.hpp
        srcs/Game/Tool/SpriteInfo.hpp
        srcs/Game/Display/IrrlichtDisplay.cpp
        srcs/Game/Display/IrrlichtDisplay.hpp
        srcs/Game/Display/IDisplay.hpp
        srcs/Game/Map/IMap.hpp
        srcs/Game/Map/ATile.cpp
        srcs/Game/Map/ATile.hpp
        srcs/Game/Display/IrrlichtDisplayLoader.cpp
        srcs/Game/Display/IrrlichtDisplayLoader.hpp
        srcs/Game/Characters/Player.cpp
        srcs/Game/Characters/Player.hpp
        srcs/Game/Characters/ACharacter.cpp
        srcs/Game/Characters/ACharacter.hpp
        srcs/Game/Display/IrrlichtDisplayLoader.cpp
        srcs/Game/Display/IrrlichtDisplayLoader.hpp
        srcs/Game/Display/IDisplayLoader.hpp
        srcs/Game/SceneManager/SceneManager.cpp
        srcs/Game/SceneManager/SceneManager.hpp)

target_link_libraries(${PROJECT_NAME} Irrlicht)