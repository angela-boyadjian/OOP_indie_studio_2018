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
    using Event = std::unique_ptr<Events>;

    Bomberman();
    ~Bomberman();

    // SETTERS
    void    setGame(std::unique_ptr<AGame> &);
    void    setDisplayer(std::unique_ptr<IDisplay> &);

    // load resources
    void loadGame();

    // Game loop
    void run();
private:
    std::unique_ptr<AGame>      _game;
    Event                       _event;

    playerVec                   _players;
    std::unique_ptr<IDisplay>   _display;
};