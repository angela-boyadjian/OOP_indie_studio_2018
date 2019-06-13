/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IrrlichtDisplay
*/
#pragma once

#include <memory>
#include <vector>
#include <irrlicht.h>

#include "Events.hpp"
#include "IDisplay.hpp"
#include "ISceneManager.hpp"
#include "GameScene.hpp"
#include "MenuScene.hpp"
// static const wchar_t *windowName = "Bomberman";

class IrrlichtDisplay : public IDisplay {
public:
    using Device = std::shared_ptr<irr::IrrlichtDevice>;
    using Gui = std::unique_ptr<irr::gui::IGUIEnvironment>;
    using AnimTerrain = std::unique_ptr<irr::scene::ISceneNodeAnimator>;
    using AnimatedMeshs = std::vector<std::unique_ptr<irr::scene::IAnimatedMesh>>;
    using AnimatedMeshsScene = std::vector<std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>>;
    using SceneNodes = std::vector<std::unique_ptr<irr::scene::ISceneNode>>;

    // NOTE CONSTRUCTOR / DESTRUCTOR
    IrrlichtDisplay();
    ~IrrlichtDisplay() = default;

    // UTILS
    irr::core::vector3df    pos3dToVector(const pos3d &);
    // SET OBJECT
    void    setDisplay(Events *) final;
    void    setBombState(const std::size_t &, bool);

    void    addNewAnimation(const char *, const char *, const pos3d &) final;

    // NOTE IS ON
    bool    isRunning() const final;

    // NOTE GUI FUNCTIONS
    void    setGuiMessage(const wchar_t *) final;

    // NOTE DRAW FUNCTIONS
    void    draw() final;

    // NOTE GET
    irr::core::dimension2du const &getScreenSize() final;
    IrrlichtDisplay::Device const &getDevice() final;
    IrrlichtDisplay::Gui const &getGui() final;
    Map3D   &getMap() final;
    Map3D   &getColiMap() final;
    Map3D   &getNonColiMap() final;
    std::vector<BombsVec>   &getBombsMap() final;

    void    addBombs(IDisplay::BombsVec &m) final { _bombs.emplace_back(std::move(m)); }
    void    setBombs(const std::size_t &, const std::size_t &, const irr::core::vector3df &) final;
   // NOTE SCENES FUNCTIONS
    void    changeScene(std::string const &) final;

    void    changeModelPos(const std::size_t &, const pos3d &) final;
    void    changeModelRot(const std::size_t &, const pos3d &) final;
    void    changeModelFrame(const std::size_t  &, const std::size_t &, const std::size_t &) final;

    // COLLISION FUNCTION
    bool    isCollision(const std::size_t &) final;
    void    destroyCollision(std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>) final;
    bool    isCollisionFromMap(irr::core::aabbox3d<irr::f32> &) const;
    bool    isCollisionFromObstacles(irr::core::aabbox3d<irr::f32> &) const;


private:
    Gui         _gui;
    std::string _currentScene;
    BombsVec    _bombsMap;
    // TEMPO
    std::vector<IDisplay::BombsVec>  _bombs;
    Map3D   _map3d;
    Map3D   _coliMap;
    Map3D   _noncoliMap;
};