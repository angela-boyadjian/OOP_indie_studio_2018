/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#pragma once

#include <memory>

#include "Map.hpp"
#include "Game.hpp"
#include "AGame.hpp"
#include "Player.hpp"
#include "DisplayLoader.hpp"

namespace core {
    class Bomberman;
}

class core::Bomberman {
public:
    using botVec = std::vector<std::unique_ptr<Bot>>;
    using playerVec = std::vector<std::unique_ptr<Player>>;
    using Event = std::unique_ptr<Events<irr::IEventReceiver>>;

    Bomberman();
    ~Bomberman();

    // SETTERS
    void    setGame(std::unique_ptr<AGame> &);
    void    setDisplayer(std::unique_ptr<IDisplay> &);

    // load resources
    void loadGame(const std::string &, std::unique_ptr<AGame> &);

    // Game loop
    void run();
private:
    std::unique_ptr<AGame>          _game;
    Event                           _event;
    std::shared_ptr<IDisplay>       _display;
    DisplayLoader                   _dispLoader;
};