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
        virtual void load(std::unique_ptr<IDisplay> &) = 0;
        virtual MapData getMapData() const = 0;
};