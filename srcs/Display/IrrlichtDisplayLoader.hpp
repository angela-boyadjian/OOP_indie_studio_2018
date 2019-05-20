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
    explicit IrrlichtDisplayLoader(const std::shared_ptr<IDisplay> &);
    ~IrrlichtDisplayLoader() = default;

    // NOTE MAP LOAD
    void loadCube(float, IDisplay::Map3D &);
    void loadMess(const SpriteInfo &, float, IDisplay::Map3D &);
    void loadMap(const MapData &) final;
    void loadMapWall(const MapData &) final;
    void addTileToMap(const irr::core::vector3df &, const SpriteInfo &, float);
    void loadMapGround(const MapData &) final;
    void loadMapEdgeTop(const MapData &map);
    void loadMapEdgeSide(const MapData &map);
    void loadMapEdgeLow(const MapData &map);
    void preloadMapWall(const MapData &) final;
    bool loadTileMap(const SpriteInfo &, float, IDisplay::Map3D &);

    // GAME LOAD
    void    loadGame(const std::unique_ptr<AGame> &) final;
    void    loadPlayer(const ACharacter::Color &, const std::vector<std::string> &) final;
    void    loadBomb(char const *, std::string const &);

private:
    std::shared_ptr<IDisplay> _d;
};