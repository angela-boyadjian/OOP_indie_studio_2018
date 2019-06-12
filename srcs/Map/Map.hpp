/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/

#pragma once

#include <string>
#include <irrlicht.h>

#include "IrrlichtDisplay/IrrlichtDisplay.hpp"
#include "MapData.hpp"
#include "IMap.hpp"
#include "ATile.hpp"
#include "Reader.hpp"

class Map : public IMap {
    public:
        using Map_Template = std::vector<std::vector<std::string>>;

        using Tile = irr::scene::ISceneNode;

        Map(std::string const &);
        ~Map();


        // LOAD MAP
        void load();
        Map_Template loadDefaultTemplate(const std::vector<std::string> &);
        void generate3dMap();
        std::unordered_map<char, SpriteInfo> loadRules(std::vector<SpriteInfo> &);
        MapData &getMapData() override;

    private:
        std::vector<ATile> _mapTiled;

        // NOTE
    private:

        std::string _filename;
        MapData _data;
        std::vector<std::unique_ptr<Tile>> _3dWall;
        Reader _reader;
};