/*
** EPITECH PROJECT, 2019
** IScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <irrlicht.h>
#include <iostream>

class IScene {
    public:
        virtual void deLoad() = 0;
        virtual void runScene() = 0;
        virtual void loadScene() = 0;
        virtual std::string getName() = 0;
};