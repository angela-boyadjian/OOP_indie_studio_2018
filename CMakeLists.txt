cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")

find_package(SFML 2.3 COMPONENTS audio REQUIRED)

include_directories(lib/irrLicht/include)

include_directories(
        srcs/Map
        srcs/Logic
        srcs/Events
        srcs/Display
        srcs/Display/IrrlichtDisplay
        srcs/Characters
        srcs/Objects
        srcs/Tool
        srcs/Core
        srcs/Menu
        srcs/Menu/BombermanMenu
        srcs/Game
        srcs/Game/SceneManager
)

add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/Map/Map.cpp
        srcs/Map/Map.hpp
        srcs/Map/IMap.hpp
        srcs/Menu/IMenu.hpp
        srcs/Menu/BombermanMenu/Menu.cpp
        srcs/Menu/BombermanMenu/Menu.hpp
        srcs/Map/ATile.cpp
        srcs/Map/ATile.hpp
        srcs/Tool/Reader.cpp
        srcs/Tool/Reader.hpp
        srcs/Tool/SpriteInfo.hpp
        srcs/Map/MapData.hpp
        srcs/Logic/AGame.hpp
        srcs/Logic/Bomberman/BombermanGame.cpp
        srcs/Logic/Bomberman/BombermanGame.hpp
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
        srcs/Display/IrrlichtDisplay/IrrlichtDisplay.cpp
        srcs/Display/IrrlichtDisplay/IrrlichtDisplay.hpp
        srcs/Display/IrrlichtDisplay/IrrlichtDisplayLoader.hpp
        srcs/Display/IrrlichtDisplay/IrrlichtDisplayLoader.cpp
        srcs/Objects/Bomb.cpp
        srcs/Objects/Bomb.hpp
        srcs/Game/ISceneManager.hpp
        srcs/Game/SceneManager/GameScene.cpp
        srcs/Game/SceneManager/GameScene.hpp
        srcs/Game/SceneManager/MenuScene.cpp
         srcs/Game/SceneManager/MenuScene.hpp
)

target_link_libraries(${PROJECT_NAME} Irrlicht sfml-audio)
