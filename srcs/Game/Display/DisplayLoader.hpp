/*
** EPITECH PROJECT, 2019
** DisplayLoader.hpp 
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

class DisplayLoader : public IDisplayLoader {
public:
    DisplayLoader() = default;
    explicit DisplayLoader(const std::shared_ptr<IDisplay> &);
    ~DisplayLoader() = default;

    // NOTE MAP LOAD
    void loadMap(const MapData &) final;
    void loadMapWall(const MapData &) final;
    void loadMapGround(const MapData &) final;
    void preloadMapWall(const MapData &) final;
    bool addTileToMap(const SpriteInfo &, float) final;

    // GAME LOAD
    void    loadGame(const std::unique_ptr<AGame> &) final;
    void    loadPlayer(const ACharacter::Color &, const std::vector<std::string> &) final;

private:
    std::shared_ptr<IDisplay> _d;
};



