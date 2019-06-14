/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IDisplay
*/


#pragma once

#include <map>
#include "ISceneManager.hpp"

class Events;
class ISceneManager;

class IDisplay {
public:
    using Object = irr::scene::ISceneNode;
    using pos3d = std::tuple<long, long, long>;
    using VideoDriver = irr::video::IVideoDriver *;
    using SceneManager = irr::scene::ISceneManager *;
    using Device = std::shared_ptr<irr::IrrlichtDevice>;
    using Gui = std::unique_ptr<irr::gui::IGUIEnvironment>;
    using Map3D = std::vector<std::unique_ptr<IDisplay::Object>>;
    using BombsVec = std::vector<std::shared_ptr<IDisplay::Object>>;
    using Scenes = std::shared_ptr<ISceneManager>;

    // SET OBJECT
    virtual void    setDisplay(Events *) = 0;
    // NOTE MESH FUNCTIONS
    virtual void    addNewAnimation(const char *, const char *, const pos3d &) = 0;
    // NOTE IS ON
    virtual bool    isRunning() const = 0;
    // NOTE GUI FUNCTIONS
    virtual void    setGuiMessage(const wchar_t *) = 0;

    // NOTE SCENES FUNCTIONS
    virtual void    changeScene(std::string const &) = 0;

    // NOTE DRAW FUNCTIONS
    virtual void    draw() = 0;

    // NOTE GETTER
    virtual irr::core::dimension2du const &getScreenSize() = 0;
    virtual Device const &getDevice() = 0;
    virtual Gui const &getGui() = 0;
    virtual Map3D   &getMap() = 0;
    virtual Map3D   &getColiMap() = 0;
    virtual Map3D   &getNonColiMap() = 0;
    virtual BombsVec   &getBombsMap() = 0;

    virtual void    changeModelPos(const std::size_t &, const pos3d &) = 0;
    virtual void    changeModelRot(const std::size_t &, const pos3d &) = 0;
    virtual void    changeModelFrame(const std::size_t  &, const std::size_t &, const std::size_t &) = 0;

    virtual bool    isCollision(const std::size_t &) = 0;
    virtual void    destroyCollision(std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>) = 0 ;
    virtual void    setBombState(const std::size_t &, bool) = 0;

    // TEMPO
    VideoDriver         _driver;
    std::vector<std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>> _meshsScene;

    // TEMPO
    std::map<std::string, Scenes> _sceneManagers;
public:
    Device              _device;
};