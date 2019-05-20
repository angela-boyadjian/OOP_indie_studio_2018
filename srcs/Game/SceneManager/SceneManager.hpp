//
// Created by dclement on 5/20/19.
//

#pragma once

#include <memory>

#include "irrlicht.h"
#include "IDisplay.hpp"

class SceneManager {
    public:
        using sceneManager = std::unique_ptr<irr::scene::ISceneManager>;

        SceneManager(IDisplay::Device const &device);
        ~SceneManager();

        void addScene();
        void createMenuScene();

    private:
        sceneManager _smgr;
        IDisplay::Device const _device;
};
