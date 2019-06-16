/*
** EPITECH PROJECT, 2019
** PauseMenu.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <chrono>
#include <ctime>

#include "PauseMenu.hpp"

PauseMenu::PauseMenu(irr::scene::ISceneNode *father,  irr::scene::ISceneManager *manager, const irr::core::dimension2du &win_size, std::shared_ptr<Events> event, std::shared_ptr<irr::IrrlichtDevice> device) :
    _win_size(win_size),
    _back(manager->addCubeSceneNode(30, father)),
    _status(false),
    _event(event),
    _start(std::chrono::system_clock::now())
{
    _back->setScale(irr::core::vector3df(0.75, 0.1, 1));
    _back->setPosition(irr::core::vector3df(-2.5, -10, 15));
    _back->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _back->setMaterialTexture(0, device->getVideoDriver()->getTexture("../resources/textures/menuPause.jpg"));
    _back->setVisible(false);
    auto rec = irr::core::rect<irr::s32>(_win_size.Width / 2 - 200, _win_size.Height - (_win_size.Height / 5), _win_size.Width / 2 + 200, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(manager->getGUIEnvironment()->addButton(rec, nullptr, -1, L"Menu !!"));
    _buttons.back()->setVisible(false);
    rec = irr::core::rect<irr::s32>(_win_size.Width / 2 - 200, _win_size.Height / 2, _win_size.Width / 2 + 200, _win_size.Height / 2 + 42);
    _buttons.emplace_back(manager->getGUIEnvironment()->addButton(rec, nullptr, -1, L"Save !!"));
    _buttons.back()->setVisible(false);
    rec = irr::core::rect<irr::s32>(_win_size.Width / 2 - 200, _win_size.Height / 8, _win_size.Width / 2 + 200, _win_size.Height / 8 + 42);
    _buttons.emplace_back(manager->getGUIEnvironment()->addButton(rec, nullptr, -1, L"Resume !!"));
    _buttons.back()->setVisible(false);
}

void PauseMenu::switchStatus()
{
    auto end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - _start).count();
    
    if (elapsed_seconds > 0) {
        _start = end;
        _status = !_status;
        for (auto &button : _buttons)
            button->setVisible(_status);
        _back->setVisible(_status);
    }
}

std::string PauseMenu::runPause(const std::string &from)
{
    if (_buttons[static_cast<int>(BUTTON::RESUME)]->isPressed())
        switchStatus();
    if (_buttons[static_cast<int>(BUTTON::MENU)]->isPressed()) {
        switchStatus();
        return "menu";
    }
    return from;
}