/*
** EPITECH PROJECT, 2019
** PauseMenu.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include <irrlicht.h>
#include <memory>
#include <vector>

#include "Events.hpp"

class PauseMenu {
    public:
        PauseMenu(irr::scene::ISceneNode *,  irr::scene::ISceneManager *, const irr::core::dimension2du &, std::shared_ptr<Events>);
        ~PauseMenu() = default;

        void switchStatus();
        bool getStatus() { return _status; };
        void runPause();

    private:
        const irr::core::dimension2du &_win_size;
        std::shared_ptr<irr::scene::ISceneNode> _back;
        std::vector<std::shared_ptr<irr::gui::IGUIButton>> _buttons;
        std::shared_ptr<Events> _event;
        bool _status;
};



