/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Display
*/
#pragma once

#include <irrlicht.h>
#include <memory>
#include <vector>

#include "IDisplay.hpp"
// static const wchar_t *windowName = "Bomberman";

class Display : public IDisplay {
public:
    using Device = std::unique_ptr<irr::IrrlichtDevice>;
    using Gui = std::unique_ptr<irr::gui::IGUIEnvironment>;
    using VideoDriver = std::unique_ptr<irr::video::IVideoDriver>;
    using SceneManager = std::unique_ptr<irr::scene::ISceneManager>;
    using AnimatedMeshs = std::vector<std::unique_ptr<irr::scene::IAnimatedMesh>>;
    using AnimatedMeshsScene = std::vector<std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>>;

    // NOTE CONSTRUCTOR / DESTRUCTOR
    Display();
    ~Display() = default;

    // NOTE MESH FUNCTIONS
    void    addNewAnimation(const char *, const char *, irr::core::vector3df);

    // NOTE IS ON
    bool    isRunning() const final;

    // NOTE GUI FUNCTIONS
    void    setGuiMessage(const wchar_t *) final;

    // NOTE CAMERA FUNCTIONS
    void    setCameraScene() final;

    // NOTE DRAW FUNCTIONS
    void    draw() final;

    Map3D   &getMap() override;

private:
    void    addNewMesh(const char *);
    void    addNewMeshScene(const char *, irr::core::vector3df);

private:
    Gui                 _gui;
    AnimatedMeshs       _meshs;
    Device              _device;

    //SceneManager        _scenes;
    AnimatedMeshsScene  _meshsScene;
    Map3D _map3d;

};