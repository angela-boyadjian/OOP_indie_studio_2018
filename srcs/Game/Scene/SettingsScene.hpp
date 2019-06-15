//
// Created by dclement on 6/15/19.
//

#pragma once

#include "IScene.hpp"
#include "Events.hpp"
#include "SceneInfo.hpp"

class SettingsScene : public IScene {
    public:
    SettingsScene(std::shared_ptr<IDisplay>, irr::scene::ISceneNode *,
        std::string const &, std::shared_ptr<Events>);
    ~SettingsScene() = default;

    void deLoad() final;
    SceneInfo runScene() final;
    void loadScene(SceneInfo &) final;
    std::string getName() final;

    private:
    std::shared_ptr<irr::scene::ISceneNode> _master;
    irr::scene::ISceneManager *_manager;
    std::string _name;
    bool _is_load;
    const irr::core::dimension2du& _win_size;
    std::shared_ptr<irr::IrrlichtDevice> _device;
    std::shared_ptr<Events> _event;
    bool _isVisible;
};
