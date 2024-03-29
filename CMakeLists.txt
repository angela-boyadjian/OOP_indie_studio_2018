cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

set(SOURCE_FILES
        srcs/main.cpp
        srcs/Map/Map.cpp
        srcs/Map/Map.hpp
        srcs/Map/IMap.hpp
        srcs/Menu/IMenu.hpp
        srcs/Events/Events.hpp
        srcs/Events/Events.cpp
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
        srcs/Game/SceneManager/MapSelectionScene.cpp
        srcs/Game/SceneManager/MapSelectionScene.hpp
        srcs/Game/Scene/MenuBisScene.hpp srcs/Game/Scene/MenuBisScene.cpp
        srcs/Game/Scene/IntroScene.hpp srcs/Game/Scene/IntroScene.cpp
        srcs/Game/Scene/IScene.hpp
        srcs/Game/Scene/SceneManager.hpp srcs/Game/Scene/SceneManager.cpp
        srcs/Game/Scene/GameBisScene.cpp srcs/Game/Scene/GameBisScene.hpp
        srcs/Game/Scene/SceneManagerException.cpp srcs/Game/Scene/SceneManagerException.hpp
        srcs/Game/Scene/SceneException.cpp srcs/Game/Scene/SceneException.hpp
        srcs/Game/Scene/MapChangeScene.cpp srcs/Game/Scene/MapChangeScene.hpp
        srcs/Game/Save/ISave.hpp
        srcs/Game/Save/SaveManager.cpp srcs/Game/Save/SaveManager.hpp
        srcs/Game/Save/ILoad.hpp
        srcs/Game/Save/LoadManager.cpp srcs/Game/Save/LoadManager.hpp
        srcs/Game/Scene/SettingsScene.cpp srcs/Game/Scene/SettingsScene.hpp srcs/Game/Scene/ChoosePlayerScene.cpp srcs/Game/Scene/ChoosePlayerScene.hpp
        srcs/Game/Scene/SceneInfo.hpp
        srcs/Game/PauseMenu.cpp srcs/Game/PauseMenu.hpp
        )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")

find_package(SFML 2.3 COMPONENTS audio REQUIRED)
include(FindPkgConfig)
find_package(Irrlicht REQUIRED)

include_directories(lib/irrLicht/include)

include_directories(
        srcs/Map
        srcs/Logic
        srcs/Events
        srcs/Display
        srcs/Display/IrrlichtDisplay
        srcs/Characters
        srcs/Characters/BombermanPlayers
        srcs/Objects
        srcs/Tool
        srcs/Core
        srcs/Menu
        srcs/Menu/BombermanMenu
        srcs/Game
        srcs/Game/SceneManager
        srcs/Game/Scene
        srcs/Game/Save
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(bomberman PRIVATE src ${IRRLICHT_INCLUDE_DIR})
target_link_libraries(bomberman ${IRRLICHT_LIBRARY})
target_link_libraries(${PROJECT_NAME} sfml-audio)
