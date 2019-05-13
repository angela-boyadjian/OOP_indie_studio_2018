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
        using Cube = irr::scene::ISceneNode;
        using Wall = irr::scene::IAnimatedMeshSceneNode;

        Map(std::string const &);
        ~Map();


        // LOAD MAP
        void preload();
        void load(Display &);
        void addTileToMap(Display &, char, irr::core::vector3df);

        void displayMap(Display &);
    private:
        std::string _filename;
        MapData _data;
        std::vector<std::unique_ptr<Cube>> _3dMap;

};