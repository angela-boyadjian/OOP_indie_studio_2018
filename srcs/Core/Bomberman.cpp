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

void core::Bomberman::run()
{
    while (_display.isRunning()) {
        for (auto const &player : _players)
            player->displayPlayer();
//        _menu->displayMenu();
       _display.draw();
    }
}

void core::Bomberman::loadGame()
{
    _display.setCameraScene();
    _display.setGuiMessage(L"hello");
    _players.push_back(std::make_unique<Player>(ACharacter::Color::BLACK,
        std::make_tuple(1, 2), _display));
    for (auto const &player : _players)
        player->loadPlayer();
//    _menu->loadMenu();
}