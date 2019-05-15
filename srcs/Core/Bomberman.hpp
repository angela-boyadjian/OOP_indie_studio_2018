/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#pragma once

#include <memory>

#include "Game.hpp"
#include "Player.hpp"

namespace core {
    class Bomberman;
}

class core::Bomberman {
public:
    using playerVec = std::vector<std::unique_ptr<Player>>;

    Bomberman();
    ~Bomberman();

    // NOTE load resources
    void loadGame();

    // NOTE Game loop
    void run();
private:
    std::unique_ptr<IGame>      _game;
    playerVec                   _players;
    std::unique_ptr<IDisplay>   _display;
};