/*
** EPITECH PROJECT, 2019
** IDisplayLoader.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "MapData.hpp"

#pragma once

class IDisplayLoader {
    public:

        // NOTE MAP LOAD
        virtual void loadMap(const MapData &) = 0;
        virtual void loadMapWall(const MapData &) = 0;
        virtual void loadMapGround(const MapData &) = 0;
        virtual void preloadMapWall(const MapData &) = 0;
        virtual bool addTileToMap(const SpriteInfo &, float) = 0;
};