cmake_minimum_required(VERSION 3.16)
project(indie_studio VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(C3PM_PROJECT_NAME indie_studio)
set(C3PM_GLOBAL_DIR /Users/clementdubois/.c3pm)

add_executable(indie_studio)

target_sources(indie_studio PRIVATE
	/Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers/ABombermanPlayer.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers/Bot.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers/Player.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/ACharacter.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Core/Bomberman.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IrrlichtDisplay/IrrlichtDisplay.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IrrlichtDisplay/IrrlichtDisplayLoader.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Events/Events.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save/LoadManager.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save/SaveManager.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/ChoosePlayerScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/GameBisScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/IntroScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/MapChangeScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/MenuBisScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneException.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneManager.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneManagerException.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SettingsScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager/GameScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager/MapSelectionScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager/MenuScene.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/PauseMenu.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Logic/Bomberman/BombermanGame.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map/ATile.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map/Map.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Menu/BombermanMenu/Menu.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Objects/Bomb.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Objects/PowerUps.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Tool/Reader.cpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/main.cpp
	/Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers/ABombermanPlayer.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers/Bot.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers/Player.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/ACharacter.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Core/Bomberman.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IrrlichtDisplay/IrrlichtDisplay.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IrrlichtDisplay/IrrlichtDisplayLoader.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/DisplayExceptions.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IDisplay.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IDisplayLoader.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Events/Events.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save/ILoad.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save/ISave.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save/LoadManager.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save/SaveManager.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/ChoosePlayerScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/GameBisScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/IScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/IntroScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/MapChangeScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/MenuBisScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneException.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneInfo.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneManager.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SceneManagerException.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene/SettingsScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager/GameScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager/MapSelectionScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager/MenuScene.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/ISceneManager.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/PauseMenu.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Logic/Bomberman/BombermanGame.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Logic/AGame.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map/ATile.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map/IMap.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map/Map.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map/MapData.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Menu/BombermanMenu/Menu.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Menu/IMenu.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Objects/Bomb.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Objects/PowerUps.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Tool/Reader.hpp /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Tool/SpriteInfo.hpp
)


target_include_directories(indie_studio PRIVATE  /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Map /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Logic /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Events /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Display/IrrlichtDisplay /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Characters/BombermanPlayers /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Objects /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Tool /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Core /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Menu /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Menu/BombermanMenu /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/SceneManager /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Scene /Users/clementdubois/Documents/Tech/c3pm/OOP_indie_studio_2018/srcs/Game/Save
			/Users/clementdubois/.c3pm/cache/Irrlicht/1.0.1/include
)

find_library(IRRLICHT Irrlicht "/Users/clementdubois/.c3pm/cache/Irrlicht/1.0.1/")




if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lXxf86vm -lXext -lX11 -lGL -lGLU")
endif ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(GLUT REQUIRED)
find_package(ZLIB REQUIRED)
set(LIBRARIES ${IRRLICHT_LIBRARY} ${OPENGL_LIBRARIES} ${X11_X11_LIB} ${GLUT_LIBRARY} ${ZLIB_LIBRARIES})

if (APPLE)
        find_library(CARBON_LIBRARY Carbon)
        find_library(COCOA_LIBRARY Cocoa)
        find_library(IOKIT_LIBRARY IOKit)
        set(OSX_LIBRARIES ${CARBON_LIBRARY} ${COCOA_LIBRARY} ${IOKIT_LIBRARY})
endif (APPLE)

target_include_directories(${C3PM_PROJECT_NAME} PRIVATE src ${IRRLICHT_INCLUDE_DIR})
target_link_libraries(${C3PM_PROJECT_NAME} PUBLIC ${OSX_LIBRARIES} ${LIBRARIES})


target_link_libraries(
	indie_studio
	PUBLIC
	
	$<$<NOT:$<STREQUAL:"${IRRLICHT}","IRRLICHT-NOTFOUND">>:${IRRLICHT}>
)
