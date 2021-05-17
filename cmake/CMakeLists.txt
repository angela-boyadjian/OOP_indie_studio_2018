cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -I /usr/local/include -v")
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

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")

#include(FindPkgConfig)

mark_as_advanced(IRRLICHT_LIBRARY IRRLICHT_INCLUDE_DIR IRRLICHT_DLL)
set(IRRLICHT_SOURCE_DIR "" CACHE PATH "Path to irrlicht source directory (optional)")


# Find include directory

if(NOT IRRLICHT_SOURCE_DIR STREQUAL "")
        set(IRRLICHT_SOURCE_DIR_INCLUDE
                "${IRRLICHT_SOURCE_DIR}/include"
                )

        set(IRRLICHT_LIBRARY_NAMES libIrrlicht.a Irrlicht Irrlicht.lib)

        if(WIN32)
                if(MSVC)
                        set(IRRLICHT_SOURCE_DIR_LIBS "${IRRLICHT_SOURCE_DIR}/lib/Win32-visualstudio")
                        set(IRRLICHT_LIBRARY_NAMES Irrlicht.lib)
                else()
                        set(IRRLICHT_SOURCE_DIR_LIBS "${IRRLICHT_SOURCE_DIR}/lib/Win32-gcc")
                        set(IRRLICHT_LIBRARY_NAMES libIrrlicht.a libIrrlicht.dll.a)
                endif()
        else()
                set(IRRLICHT_SOURCE_DIR_LIBS "${IRRLICHT_SOURCE_DIR}/lib/Linux")
                set(IRRLICHT_LIBRARY_NAMES libIrrlicht.a)
        endif()

        find_path(IRRLICHT_INCLUDE_DIR NAMES irrlicht.h
                PATHS
                ${IRRLICHT_SOURCE_DIR_INCLUDE}
                NO_DEFAULT_PATH
                )

        find_library(IRRLICHT_LIBRARY NAMES ${IRRLICHT_LIBRARY_NAMES}
                PATHS
                ${IRRLICHT_SOURCE_DIR_LIBS}
                NO_DEFAULT_PATH
                )

else()
        find_path(IRRLICHT_INCLUDE_DIR NAMES irrlicht.h
                PATHS
                /usr/local/include/irrlicht
                /usr/include/irrlicht
                /system/develop/headers/irrlicht #Haiku
                )

        find_library(IRRLICHT_LIBRARY NAMES libIrrlicht.so libIrrlicht.a Irrlicht
                PATHS
                /usr/local/lib
                /usr/lib
                /system/develop/lib # Haiku
                )
endif()


# On Windows, find the DLL for installation
if(WIN32)
        if(MSVC)
                set(IRRLICHT_COMPILER "VisualStudio")
        else()
                set(IRRLICHT_COMPILER "gcc")
        endif()
        find_file(IRRLICHT_DLL NAMES Irrlicht.dll
                PATHS
                "${IRRLICHT_SOURCE_DIR}/bin/Win32-${IRRLICHT_COMPILER}"
                DOC "Path of the Irrlicht dll (for installation)"
                )
endif(WIN32)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Irrlicht DEFAULT_MSG IRRLICHT_LIBRARY IRRLICHT_INCLUDE_DIR)

#find_package(Irrlicht REQUIRED)
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

target_include_directories(bomberman PUBLIC src ${IRRLICHT_INCLUDE_DIR})
target_link_libraries(bomberman PUBLIC ${OSX_LIBRARIES})
target_link_libraries(bomberman PUBLIC ${LIBRARIES})

target_link_libraries(${PROJECT_NAME})
