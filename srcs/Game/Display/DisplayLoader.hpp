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

class DisplayLoader {

        using Object = irr::scene::ISceneNode;
        using Map3D = std::vector<std::unique_ptr<DisplayLoader::Object>>;

    public:
        DisplayLoader(const std::shared_ptr<IDisplay> &);
        ~DisplayLoader();


        // NOTE MAP LOAD
        Map3D loadMap(std::unique_ptr<IMap> &);
        void loadMapWall(Map3D &, std::unique_ptr<IMap> &);
        void loadMapGround(Map3D &, std::unique_ptr<IMap> &);
        void preloadMapWall(Map3D &, std::unique_ptr<IMap> &);
        bool addTileToMap(const SpriteInfo &, float , DisplayLoader::Map3D &);


    private:
        std::shared_ptr<IDisplay> _d;

};



