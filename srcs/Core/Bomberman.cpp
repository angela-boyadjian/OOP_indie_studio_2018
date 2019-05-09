/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/
#include <iostream>
#include "Bomberman.hpp"

core::Bomberman::Bomberman()
{
}

core::Bomberman::~Bomberman()
{
}

void core::Bomberman::run()
{
    Display d;

    _player = std::make_unique<Player>(std::make_tuple(1, 2), d);
    _player->loadPlayer();

    d.setCameraScene();
    while (d.isRunning())
        _player->displayPlayer();
}
