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
#include "IDisplayLoader.hpp"

class DisplayLoader : public IDisplayLoader{

    public:
        DisplayLoader(const std::shared_ptr<IDisplay> &);
        ~DisplayLoader() = default;


        // NOTE MAP LOAD
        void loadMap(const MapData &) override;
        void loadMapWall(const MapData &) override;
        void loadMapGround(const MapData &) override;
        void preloadMapWall(const MapData &) override;
        bool addTileToMap(const SpriteInfo &, float) override;


    private:
        std::shared_ptr<IDisplay> _d;

};



