/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/

#pragma once

#include <string>
#include <irrlicht.h>

#include "IrrlichtDisplay.hpp"
#include "MapData.hpp"
#include "IMap.hpp"
#include "ATile.hpp"

class Map : public IMap {
    public:
        using Tile = irr::scene::ISceneNode;

        Map(std::string const &);
        ~Map();


        // LOAD MAP
        void load();
        std::unordered_map<char, SpriteInfo> loadRules(std::vector<SpriteInfo> &);
        MapData getMapData() const override;

    private:
        std::vector<ATile> _mapTiled;

        // NOTE
    private:
        std::string _filename;
        MapData _data;
        std::vector<std::unique_ptr<Tile>> _3dWall;
};