/*
** EPITECH PROJECT, 2019
** MapChangeScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include <IDisplay.hpp>
#include <IMap.hpp>

#include "IScene.hpp"
#include "SceneInfo.hpp"

class MapChangeScene : public IScene {
    public:
        MapChangeScene(std::shared_ptr<IDisplay>, irr::scene::ISceneNode *,
                       std::string const &);
        ~MapChangeScene() = default;

        // MANDATORY
        void deLoad() final;
        SceneInfo runScene() final;
        void loadScene(SceneInfo &) final;
        std::string getName() final;

    private:
        std::shared_ptr<irr::scene::ISceneNode> _master;
        irr::scene::ISceneManager *_manager;
        std::string _name;
        bool _is_load;
        std::vector<std::shared_ptr<irr::scene::ISceneNode>> _cubes;
        std::vector<irr::gui::IGUIButton *> _buttons;
        const irr::core::dimension2du &_win_size;
        std::shared_ptr<irr::IrrlichtDevice> _device;
        std::unique_ptr<IMap> _map;
        const std::shared_ptr<IDisplay> _display;
        irr::scene::ICameraSceneNode *_camera;
        SceneInfo _info;
};



