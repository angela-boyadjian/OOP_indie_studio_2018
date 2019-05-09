/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#pragma once

#include <memory>

#include "Player.hpp"

namespace core {
    class Bomberman;
}

class core::Bomberman {
public:
    Bomberman();
    ~Bomberman();

    // NOTE load resources
    void loadGame();

    // NOTE Game loop
    void run();
private:
    std::unique_ptr<Player> _player;
    Display                 _display;
};