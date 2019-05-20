/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IDisplay
*/


#pragma once

#include "Events.hpp"

class Events;

class IDisplay {
public:
    using Object = irr::scene::ISceneNode;
    using pos3d = std::tuple<long, long, long>;
    using VideoDriver = irr::video::IVideoDriver *;
    using SceneManager = irr::scene::ISceneManager *;
    using Device = std::shared_ptr<irr::IrrlichtDevice>;
    using Map3D = std::vector<std::unique_ptr<IDisplay::Object>>;

    // SET OBJECT
    virtual void    setDisplay(Events *) = 0;
    // NOTE MESH FUNCTIONS
    virtual void    addNewAnimation(const char *, const char *, const pos3d &) = 0;
    // NOTE IS ON
    virtual bool    isRunning() const = 0;
    // NOTE GUI FUNCTIONS
    virtual void    setGuiMessage(const wchar_t *) = 0;
    // NOTE CAMERA FUNCTIONS
    virtual void    setCameraScene() = 0;
    //    // NOTE DRAW FUNCTIONS
    virtual void    draw() = 0;

    virtual Map3D   &getMap() = 0;

    virtual void    changeModelPos(const std::size_t &, const pos3d &) = 0;
    virtual void    changeModelRot(const std::size_t &, const pos3d &) = 0;
    virtual void    changeModelFrame(const std::size_t  &, const std::size_t &, const std::size_t &) = 0;

    virtual bool    isCollision(const std::size_t &) = 0;
    virtual void    destroyCollision(const std::size_t &) = 0;

    // TEMPO
    SceneManager        _scenes;
    VideoDriver         _driver;

public:
    Device              _device;
};