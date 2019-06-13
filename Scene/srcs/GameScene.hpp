/*
** EPITECH PROJECT, 2019
** GameScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "IScene.hpp"

class GameScene : public IScene {
    public:
        GameScene(irr::scene::ISceneManager *, irr::scene::ISceneNode *, const std::string &);
        ~GameScene() = default;

        // MANDATORY
        void deLoad() override;
        void runScene() override;
        void loadScene() override;
        std::string getName() override;

    private:
        std::shared_ptr<irr::scene::ISceneNode> _master;
        irr::scene::ISceneManager *_manager;
        std::string _name;
        bool _is_load;
        std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
};



