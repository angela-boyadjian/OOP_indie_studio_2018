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
#include <chrono>

#include "IScene.hpp"
#include "Events.hpp"

class IntroScene : public IScene {
public:
    using Timer = std::chrono::time_point<std::chrono::steady_clock,
        std::chrono::nanoseconds>;
    IntroScene(std::shared_ptr<irr::IrrlichtDevice>, irr::scene::ISceneNode *,
        std::string const &, const irr::core::dimension2du &, irr::video::IVideoDriver *, std::shared_ptr<Events>);
    ~IntroScene() = default;

public:
    void deLoad() final;
    std::string runScene() final;
    void loadScene() final;
    std::string getName() final;

private:
    void loadImg() noexcept;
    void updateImg();
    std::size_t getElapsedTime() const;

private:
    Timer   _clock;
    std::shared_ptr<irr::scene::ISceneNode> _master;
    irr::scene::ISceneManager *_manager;
    std::string _name;
    bool _is_load;
    std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
    std::array<irr::gui::IGUIImage *, 2>    _images;
    std::array<irr::video::ITexture *, 2>   _textures;
    const irr::core::dimension2du& _win_size;
    std::shared_ptr<irr::IrrlichtDevice> _device;
    std::shared_ptr<Events> _event;
    bool _isVisible;
};