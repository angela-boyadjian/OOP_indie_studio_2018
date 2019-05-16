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
#include "ACharacter.hpp"

class DisplayLoader {

    public:
        DisplayLoader() = default;
        explicit DisplayLoader(const std::shared_ptr<IDisplay> &);
        ~DisplayLoader() = default;


        // NOTE MAP LOAD
        void loadMap(const MapData &);
        void loadMapWall(const MapData &);
        void loadMapGround(const MapData &);
        void preloadMapWall(const MapData &);
        bool addTileToMap(const SpriteInfo &, float);

        // PLAYER LOAD
        void    loadPlayer(const ACharacter::Color &, const std::vector<std::string> &);

    private:
        std::shared_ptr<IDisplay> _d;

};



