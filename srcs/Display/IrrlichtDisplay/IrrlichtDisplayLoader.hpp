/*
** EPITECH PROJECT, 2019
** IrrlichtDisplayLoader.hpp
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include <irrlicht.h>
#include <vector>
#include <iostream>
#include <memory>

#include "IMap.hpp"
#include "AGame.hpp"
#include "ACharacter.hpp"
#include "IDisplayLoader.hpp"

class IrrlichtDisplayLoader : public IDisplayLoader {
public:
    IrrlichtDisplayLoader() = default;
    explicit IrrlichtDisplayLoader(const std::shared_ptr<IDisplay> &, std::shared_ptr<irr::scene::ISceneNode> &, irr::scene::ISceneManager *);
    ~IrrlichtDisplayLoader() = default;

    // NOTE MAP LOAD
    void loadCube(float, IDisplay::Map3D &);
    void loadMess(const SpriteInfo &, float, IDisplay::Map3D &);
    void loadMap(const MapData &) final;
    void loadMapWall(const MapData &) final;
    void addTileToMap(const irr::core::vector3df &, const SpriteInfo &, float);
    void loadMapGround(const MapData &) final;
    void loadMapEdgeTop(const MapData &);
    void loadMapEdgeSide(const MapData &);
    void loadMapEdgeLow(const MapData &);
    void loadEdge(const MapData &);

    //void loadMap
    void preloadMapWall(const MapData &) final;
    bool loadTileMap(const SpriteInfo &, float, IDisplay::Map3D &);

    // NOTE MENU LOAD
    void loadMenu(const std::unique_ptr<Menu> &) final;

    // GAME LOAD
    void    setExplosionPos();
    void    loadExplosion(std::size_t, std::size_t);
    void    setBombsPos();
    void    loadBomb_b2(std::size_t, std::size_t);
    void    loadBomb(Bomb &, IDisplay::BombsVec &);
    void    loadGame(const std::unique_ptr<AGame> &) final;
    void    loadPlayer(const ACharacter::Color &, const std::vector<std::string> &) final;

private:
    std::shared_ptr<IDisplay> _d;
    std::shared_ptr<irr::scene::ISceneNode> _father;
    irr::scene::ISceneManager * _manager;
};
