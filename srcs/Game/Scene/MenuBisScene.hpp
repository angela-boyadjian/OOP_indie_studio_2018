/*
** EPITECH PROJECT, 2019
** MenuScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <memory>
#include <vector>

#include "IScene.hpp"

class MenuBisScene : public IScene {
    public:
        MenuBisScene(irr::scene::ISceneManager *, irr::scene::ISceneNode *, const std::string &);
        ~MenuBisScene() = default;

        // MANDATORY
        void deLoad() override;
        std::string runScene() override;
        void loadScene() override;
        std::string getName() override;

    private:
        std::shared_ptr<irr::scene::ISceneNode> _master;
        irr::scene::ISceneManager *_manager;
        std::string _name;
        bool _is_load;
        std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
        irr::gui::IGUIButton *_bouton;

};



