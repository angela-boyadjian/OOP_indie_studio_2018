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
        void addTileToMap(Display &, char, irr::core::vector3df, std::unordered_map<char, SpriteInfo> &, float size);

        void displayMap(Display &);
    private:
        std::string _filename;
        MapData _data;
        std::vector<std::unique_ptr<Tile>> _3dMap;
};