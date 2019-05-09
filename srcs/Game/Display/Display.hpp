#pragma once

#include <irrlicht.h>
#include <memory>
#include <vector>

using Device = irr::IrrlichtDevice *;
using Gui = irr::gui::IGUIEnvironment *;
using VideoDriver = irr::video::IVideoDriver *;
using SceneManager = irr::scene::ISceneManager *;
using AnimatedMeshs = std::vector<irr::scene::IAnimatedMesh *>;
using AnimatedMeshsScene = std::vector<irr::scene::IAnimatedMeshSceneNode *>;

static const wchar_t *windowName = L"Bomberman";

class Display {
public:
    // CONSTRUCTOR / DESTRUCTOR
    Display();
    ~Display() = default;

    // MESH FUNCTIONS
    void    addNewMesh(const char *);
    void    addNewMeshScene(const char *);
    void    addNewAnimation(const char *, const char *);

    // IS ON
    bool    isRunning() const;

    // GUI FUNCTIONS
    void    setGuiMessage(const wchar_t *);

    // CAMERA FUNCTIONS
    void    setCameraScene();

    // DRAW FUNCTIONS
    void    draw();
private:
    Gui                 _gui;
    AnimatedMeshs       _meshs;
    Device              _device;
    VideoDriver         _driver;
    SceneManager        _scenes;
    AnimatedMeshsScene  _meshsScene;
};