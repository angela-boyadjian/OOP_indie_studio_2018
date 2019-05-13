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

// static const wchar_t *windowName = "Bomberman";

class Display {
public:
    using Device = irr::IrrlichtDevice *;
    using Gui = irr::gui::IGUIEnvironment *;
    using VideoDriver = irr::video::IVideoDriver *;
    using SceneManager = irr::scene::ISceneManager *;
    using AnimatedMeshs = std::vector<irr::scene::IAnimatedMesh *>;
    using AnimatedMeshsScene = std::vector<irr::scene::IAnimatedMeshSceneNode *>;

    // NOTE CONSTRUCTOR / DESTRUCTOR
    Display();
    ~Display() = default;

    // NOTE MESH FUNCTIONS
    void    addNewAnimation(const char *, const char *, irr::core::vector3df);

    // NOTE IS ON
    bool    isRunning() const;

    // NOTE GUI FUNCTIONS
    void    setGuiMessage(const wchar_t *);

    // NOTE CAMERA FUNCTIONS
    void    setCameraScene();

    // NOTE DRAW FUNCTIONS
    void    draw();

        SceneManager        _scenes; // TEMPO
        VideoDriver         _driver;
private:
    void    addNewMesh(const char *);
    void    addNewMeshScene(const char *, irr::core::vector3df);

private:
    Gui                 _gui;
    AnimatedMeshs       _meshs;
    Device              _device;

    //SceneManager        _scenes;
    AnimatedMeshsScene  _meshsScene;
};