/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IMap
*/

#pragma once

#include <memory>

#include "IDisplay.hpp"

class IMap {
public:
    // LOAD MAP
    virtual void preload() = 0;
    virtual void load(std::unique_ptr<IDisplay> &) = 0;
    virtual void loadWall(std::unique_ptr<IDisplay> &) = 0;
    virtual void loadGround(std::unique_ptr<IDisplay> &) = 0;
//    void addTileToMap(std::unique_ptr<IDisplay> &, char, irr::core::vector3df, std::unordered_map<char, SpriteInfo> &, float size);

    virtual void displayMap(std::unique_ptr<IDisplay> &) = 0;
};