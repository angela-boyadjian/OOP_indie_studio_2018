/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Bomberman.hpp"

#include "Map.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "Display.hpp"

#include <irrlicht.h>

int main()
{
    Map map("./../resources/maps/3");
    Display d;

    map.load(d);
    while (d.isRunning())
        d.draw();
    return 0;
    core::Bomberman b;

    auto disp = std::unique_ptr<IDisplay>(new Display());
//    auto game = std::unique_ptr<AGame>(new Game());
    b.setDisplayer(disp);
    b.loadGame();
    b.run();
    return 0;
}