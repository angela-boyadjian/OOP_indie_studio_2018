/*
** EPITECH PROJECT, 2019
** MenuScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <memory>

#include "IScene.hpp"

class MenuScene : public IScene {
    public:
        MenuScene(std::shared_ptr<irr::scene::ISceneManager>);
        ~MenuScene() = default;

        void runScene() override;
        void loadScene() override;
        std::string getName() override;

    private:
        std::shared_ptr<irr::scene::ISceneNode> _master;
        std::string _name;
};



