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

        enum class BUTTON {
                MENU = 0,
                SAVE,
                RESUME,
        };

        PauseMenu(irr::scene::ISceneNode *,  irr::scene::ISceneManager *, const irr::core::dimension2du &, std::shared_ptr<Events>, std::shared_ptr<irr::IrrlichtDevice>);
        ~PauseMenu() = default;

        void switchStatus();
        bool getStatus() { return _status; };
        std::string runPause(const std::string &);

    private:
        const irr::core::dimension2du &_win_size;
        std::shared_ptr<irr::scene::ISceneNode> _back;
        std::vector<std::shared_ptr<irr::gui::IGUIButton>> _buttons;
        std::shared_ptr<Events> _event;
        bool _status;
        int _delay;
        std::chrono::time_point<std::chrono::system_clock> _start;
};



