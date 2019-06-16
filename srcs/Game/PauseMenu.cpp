/*
** EPITECH PROJECT, 2019
** PauseMenu.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "PauseMenu.hpp"

PauseMenu::PauseMenu(irr::scene::ISceneNode *father,  irr::scene::ISceneManager *manager, const irr::core::dimension2du &win_size, std::shared_ptr<Events> event) :
    _win_size(win_size),
    _back(manager->addCubeSceneNode(100, father)),
    _status(false),
    _event(event)
{
    _back->setScale(irr::core::vector3df(0, 0.1, 0));
    _back->setPosition(irr::core::vector3df(0, 0, 0));
}

void PauseMenu::switchStatus()
{
    _status = !_status;
    _back->setVisible(_status);
}

void PauseMenu::runPause()
{
    std::cout << "coucou" << std::endl;
    if (_event->IsKeyDown(irr::KEY_ESCAPE))
        switchStatus();
    while (_status) {
        if (_event->IsKeyDown(irr::KEY_ESCAPE))
            switchStatus();
        std::cout << "aie" << std::endl;
    }
}