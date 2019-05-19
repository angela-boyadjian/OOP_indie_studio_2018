/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Display
*/
#pragma once

#include <memory>
#include <vector>
#include <irrlicht.h>

#include "Events.hpp"
#include "IDisplay.hpp"
// static const wchar_t *windowName = "Bomberman";

class Display : public IDisplay {
public:
    using Device = std::shared_ptr<irr::IrrlichtDevice>;
    using Gui = std::unique_ptr<irr::gui::IGUIEnvironment>;
    using Camera = std::unique_ptr<irr::scene::ICameraSceneNode>;
    using VideoDriver = std::unique_ptr<irr::video::IVideoDriver>;
    using Selector = std::unique_ptr<irr::scene::ITriangleSelector>;
    using SceneManager = std::unique_ptr<irr::scene::ISceneManager>;
    using AnimTerrain = std::unique_ptr<irr::scene::ISceneNodeAnimator>;
    using AnimatedMeshs = std::vector<std::unique_ptr<irr::scene::IAnimatedMesh>>;
    using AnimatedMeshsScene = std::vector<std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>>;

    // NOTE CONSTRUCTOR / DESTRUCTOR
    Display();
    ~Display() = default;

    // UTILS
    irr::core::vector3df    pos3dToVector(const pos3d &);
    // SET OBJECT
    void    setDisplay(Events *) final;
    void    setTerrain();
    void    setSkyDome();
    void    initTerrain();
    void    initAnimTerrain();
    void    setTerrainMaterial();

    // NOTE MESH FUNCTIONS
    void    setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *);
    void    setMeshFrames(irr::scene::IAnimatedMeshSceneNode *);
    void    setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *);
    void    addNewAnimation(const char *, const char *, const pos3d &) final;

    // NOTE IS ON
    bool    isRunning() const final;

    // NOTE GUI FUNCTIONS
    void    setGuiMessage(const wchar_t *) final;

    // NOTE CAMERA FUNCTIONS
    void    setCameraScene() final;

    // NOTE DRAW FUNCTIONS
    void    draw() final;

    // NOTE GET
    irr::core::dimension2du const &getScreenSize();
    Display::Device const &getDevice();
    Display::Gui const &getGui();
    Map3D   &getMap() override;

    void    changeModelPos(const std::size_t &, const pos3d &) final;
    void    changeModelRot(const std::size_t &, const pos3d &) final;
    void    changeModelFrame(const std::size_t  &, const std::size_t &, const std::size_t &) final;

    bool    isCollision(const std::size_t &) final;
    void    destroyCollision(const std::size_t &) final;
private:
    void    addNewMesh(const char *);
    void    addNewMeshScene(const char *, const irr::core::vector3df &);

private:
    Gui                 _gui;
    AnimatedMeshs       _meshs;
    Camera              _camera;
    Selector            _selector;
    AnimTerrain         _animTerrain;
    irr::scene::ITerrainSceneNode   *_terrain;
    //SceneManager        _scenes;
    AnimatedMeshsScene  _meshsScene;
    Map3D _map3d;

};