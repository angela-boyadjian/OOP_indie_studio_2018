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
        SceneManager(std::shared_ptr<irr::scene::ISceneManager>);
        ~SceneManager() = default;

        void addScenes(std::unique_ptr<IScene>);
        std::tuple<long, std::string> getCurrent() const;
        void setCurrent(const std::string &);
        void setCurrent(const long);
        std::shared_ptr<irr::scene::ISceneManager> &getMaster();
    private:
        std::vector<std::unique_ptr<IScene>> _scenes;
        std::tuple<long, std::string> _current;
        std::shared_ptr<irr::scene::ISceneManager> _master;
};



