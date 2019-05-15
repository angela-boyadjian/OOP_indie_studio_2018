//
// Created by dclement on 5/12/19.
//

#include "Menu.hpp"
#include "irrlicht.h"
#include "driverChoice.h"
#include "Display.hpp"
#include "Events.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::load(Display &display)
{
    Display::Gui gui = display.getGui();
    Display::Device device = display.getDevice();
    auto screenSize = display.getScreenSize();

    gui->addButton(irr::core::rect<irr::s32>(10, 240, 110, 240 + 32), 0,
    101, L"Quit", L"Exits Program");
    gui->addButton(irr::core::rect<irr::s32>(screenSize.Width - 110, 240, screenSize.Width - 10, 240 + 32), 0,
        101, L"Start Game", L"Start Game");
}
