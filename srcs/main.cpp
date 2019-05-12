/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Bomberman.hpp"

#include <irrlicht.h>

int main()
{
    core::Bomberman b;

    b.loadGame();
    b.run();
    return 0;
}