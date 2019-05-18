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
#include "IDisplayLoader.hpp"

namespace core {
    class Bomberman;
}

class core::Bomberman {
public:
    using Event = std::unique_ptr<Events>;
    using botVec = std::vector<std::unique_ptr<Bot>>;
    using playerVec = std::vector<std::unique_ptr<Player>>;

    Bomberman();
    ~Bomberman();

    // SETTERS
    void    setGame(std::unique_ptr<AGame> &);
    void    setDisplayer(std::shared_ptr<IDisplay> &, std::unique_ptr<IDisplayLoader> &);

    // load resources
    void    loadGame(const std::string &, std::unique_ptr<AGame> &);

    // Game loop
    void    run();
    void    changeAnimation(const std::size_t &, const ACharacter::Action &, const ACharacter::Action &);
    void    changeFrameAndPos(const std::size_t &, const ACharacter::Action &, const ACharacter::Action &);

    // LAUNCH CORE
    void    lauch();
    void    initGame();

private:
    std::unique_ptr<IMap>           _map;
    std::unique_ptr<AGame>          _game;
    Event                           _event;
    std::shared_ptr<IDisplay>       _display;
    std::unique_ptr<IDisplayLoader> _dispLoader;
};