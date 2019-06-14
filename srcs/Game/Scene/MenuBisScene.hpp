/*
** EPITECH PROJECT, 2019
** MenuScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <memory>
#include <vector>

#include "IDisplay.hpp"
#include "IScene.hpp"

class MenuBisScene : public IScene {
public:
    MenuBisScene(std::shared_ptr<IDisplay>, irr::scene::ISceneNode *, std::string const &);
    ~MenuBisScene() = default;

public:
    void deLoad() override;
    std::string runScene() override;
    void loadScene() override;
    std::string getName() override;

private:
    void loadButtons();

private:
    std::shared_ptr<irr::scene::ISceneNode> _master;
    irr::scene::ISceneManager *_manager;
    std::string _name;
    bool _is_load;
    std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
    std::vector<irr::gui::IGUIButton *> _buttons;
    const irr::core::dimension2du& _win_size;
    std::shared_ptr<irr::IrrlichtDevice> _device;
<<<<<<< HEAD
=======
    irr::gui::IGUIImage     *_background;
    irr::video::ITexture    *_texture;
>>>>>>> 7dff65465ec6cc02b0d25b26939fd1fd4df5e510
};