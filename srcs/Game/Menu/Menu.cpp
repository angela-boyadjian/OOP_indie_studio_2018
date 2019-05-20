//
// Created by dclement on 5/12/19.
//

#include "Menu.hpp"
#include "irrlicht.h"
#include "driverChoice.h"
#include "IrrlichtDisplay.hpp"
#include "Events.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::load(IrrlichtDisplay &display)
{
    IrrlichtDisplay::Gui const &gui = display.getGui();
    IrrlichtDisplay::Device const &device = display.getDevice();
    auto screenSize = display.getScreenSize();

    gui->addButton(irr::core::rect<irr::s32>(10, 240, 110, 240 + 32), 0,
    101, L"Quit", L"Exits Program");
    gui->addButton(irr::core::rect<irr::s32>(screenSize.Width - 110, 240, screenSize.Width - 10, 240 + 32), 0,
        101, L"Start BombermanGame", L"Start BombermanGame");
    Events *receiver = new Events(device);
    device->setEventReceiver(receiver);
}
