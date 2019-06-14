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
    MenuBisScene(std::shared_ptr<irr::IrrlichtDevice>, irr::scene::ISceneNode *, const std::string &, const irr::core::dimension2du&);
    ~MenuBisScene() = default;

    // MANDATORY
    void deLoad() override;
    std::string runScene() override;
    void loadScene() override;
    std::string getName() override;

    // ONLY MENU
    void loadBoutons();

private:
    std::shared_ptr<irr::scene::ISceneNode> _master;
    irr::scene::ISceneManager *_manager;
    std::string _name;
    bool _is_load;
    std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
    std::vector<irr::gui::IGUIButton *> _boutons;
    const irr::core::dimension2du& _win_size;
    std::shared_ptr<irr::IrrlichtDevice> _device;
};