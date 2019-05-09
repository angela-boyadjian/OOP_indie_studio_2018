/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Map.hpp"
#include "Display.hpp"

#include <irrlicht.h>

int main()
{
    Display d;

    d.addNewAnimation("../resources/models/Character/Bomberman.MD3",
        "../resources/models/Character/RedBombermanTextures.png");
    d.setCameraScene();
    while (d.isRunning())
        d.draw();
    return 0;
}