//
// Created by dclement on 5/12/19.
//

#include "Menu.hpp"
#include "irrlicht.h"
#include "driverChoice.h"

Menu::Menu(Display &display) : _display(display)
{

}

Menu::~Menu()
{

}

void Menu::loadMenu()
{
    _display.setButton();
}

void Menu::displayMenu()
{
    _display.draw();
}
