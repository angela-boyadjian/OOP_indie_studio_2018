/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/
#include <iostream>

#include "Bomberman.hpp"
#include "ACharacter.hpp"

core::Bomberman::Bomberman()
{
}

core::Bomberman::~Bomberman()
{
}

// SETTERS
void    core::Bomberman::setGame(std::unique_ptr<AGame> &g)
{
    _game = std::move(g);
}

void    core::Bomberman::setDisplayer(std::unique_ptr<IDisplay> &d)
{
    _display = std::move(d);
}

void core::Bomberman::run()
{
    while (_display->isRunning()) {
        for (auto const &player : _players)
            player->displayPlayer();
    }
}

void core::Bomberman::loadGame()
{
    _display->setCameraScene();
    _players.push_back(std::make_unique<Player>(ACharacter::Color::BLACK,
        std::make_tuple(1, 2)));
    for (auto const &player : _players)
        player->loadPlayer();
}