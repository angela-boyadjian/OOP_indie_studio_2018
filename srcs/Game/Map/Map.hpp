/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/

#pragma once

#include <string>
#include <irrlicht.h>

#include "Display.hpp"
#include "MapData.hpp"
#include "IMap.hpp"
#include "ATile.hpp"

class Map {
    public:
        using Tile = irr::scene::ISceneNode;

        Map(std::string const &);
        ~Map();


        // LOAD MAP
        void preload();
        void load(Display &);
        void loadWall(Display &);
        void loadGround(Display &);
        void preloadWall(Display &);
        bool addTileToMap(Display &, const SpriteInfo &, float);

        void displayMap(Display &);

        MapData getMapData() const;


    private:
        std::vector<ATile> _mapTiled;

        // NOTE
    private:
        std::string _filename;
        MapData _data;
        std::vector<std::unique_ptr<Tile>> _3dWall;
};