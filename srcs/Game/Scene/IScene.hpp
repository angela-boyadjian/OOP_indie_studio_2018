/*
** EPITECH PROJECT, 2019
** IScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <irrlicht.h>
#include <iostream>

#include "SceneInfo.hpp"

class IScene {
    public:
        virtual void deLoad() = 0;
        virtual SceneInfo runScene() = 0;
        virtual void loadScene(SceneInfo &) = 0;
        virtual std::string getName() = 0;
};