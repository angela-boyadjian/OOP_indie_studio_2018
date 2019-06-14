/*
** EPITECH PROJECT, 2019
** SceneManager.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <irrlicht.h>

#include "IScene.hpp"

class SceneManager {
    public:
        SceneManager();
        ~SceneManager() = default;

        void initManager(irr::scene::ISceneManager *);
        void loadCurrent();
        void runCurrentScene();
        void setCurrent(const unsigned long);
        void setCurrent(const std::string &);
        void changeCurrent(const unsigned long);
        void changeCurrent(const std::string &);
        irr::scene::ISceneManager *getManager();
        irr::scene::ISceneNode *getMaster();
        void addScenes(std::unique_ptr<IScene> scene);
        std::tuple<long, std::string> getCurrent() const;

    private:
        irr::scene::ISceneManager *_manager;
        irr::scene::ISceneNode *_master;
        std::tuple<unsigned long, std::string> _current;
        std::vector<std::unique_ptr<IScene>> _scenes;
        irr::gui::IGUIEnvironment *_gui;
};



