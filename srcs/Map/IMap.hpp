/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IMap
*/

#pragma once

#include <memory>

#include "IDisplay.hpp"
#include "SpriteInfo.hpp"
#include "MapData.hpp"

class IMap {
    public:
        // LOAD MAP
        virtual void load(const std::string &) = 0;
        virtual MapData &getMapData() = 0;
        virtual void generate3dMap(int map_i, int rand, long seed) = 0;
};