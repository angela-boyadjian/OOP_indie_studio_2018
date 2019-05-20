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
    void loadCube(float);
    void loadMess(const SpriteInfo &, float);
    void loadMap(const MapData &) final;
    void loadMapWall(const MapData &) final;
    void addTileToMap(const irr::core::vector3df &, const SpriteInfo &);
    void loadMapGround(const MapData &) final;
    void preloadMapWall(const MapData &) final;
    bool loadTileMap(const SpriteInfo &, float) final;

    // GAME LOAD
    void    loadGame(const std::unique_ptr<AGame> &) final;
    void    loadPlayer(const ACharacter::Color &, const std::vector<std::string> &) final;

private:
    std::shared_ptr<IDisplay> _d;
};



