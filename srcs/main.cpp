/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Bomberman.hpp"


#include "Map.hpp"
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

    b.loadGame();
    b.run();
    return 0;
}