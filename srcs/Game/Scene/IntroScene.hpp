/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IntroScene
*/

#pragma once

#include <memory>
#include <vector>
#include <array>

#include "IScene.hpp"

class IntroScene : public IScene {
public:
    IntroScene(std::shared_ptr<irr::IrrlichtDevice>, irr::scene::ISceneNode *,
        std::string const &, const irr::core::dimension2du &, irr::video::IVideoDriver *);
    ~IntroScene() = default;

public:
    void deLoad() final;
    std::string runScene() final;
    void loadScene() final;
    std::string getName() final;

private:
    std::shared_ptr<irr::scene::ISceneNode> _master;
    irr::scene::ISceneManager *_manager;
    std::string _name;
    bool _is_load;
    std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
    std::array<irr::gui::IGUIImage *, 2> _images;
    std::array<irr::video::ITexture *, 2> _textures;
    const irr::core::dimension2du& _win_size;
    std::shared_ptr<irr::IrrlichtDevice> _device;
};