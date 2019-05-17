/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#include <iostream>
#include <DisplayLoader.hpp>

#include "Bomberman.hpp"
#include "ACharacter.hpp"

core::Bomberman::Bomberman()
{
}

core::Bomberman::~Bomberman()
{
}

// SETTERS
void core::Bomberman::setGame(std::unique_ptr<AGame> &g)
{
    _game = std::move(g);
}

void core::Bomberman::setDisplayer(std::shared_ptr<IDisplay> &d,
        std::unique_ptr<IDisplayLoader> &dl)
{
    _display = std::move(d);
    _dispLoader = std::move(dl);
}

void core::Bomberman::run()
{
    while (_display->isRunning()) {
        _display->draw();
    }
}

void core::Bomberman::loadGame(const std::string &mapPath, std::unique_ptr<AGame> &game)
{
    auto map = std::unique_ptr<IMap>(new Map(mapPath));
    map->load();
    _game = std::move(game);
    _display->setCameraScene();
    _dispLoader->loadGame(_game);
    _dispLoader->loadMap(map->getMapData());
}

void    core::Bomberman::lauch()
{
    auto disp = std::shared_ptr<IDisplay>(new Display());
    std::cout << "1" << std::endl;
    _event = std::make_unique<Events>(Events(disp->_device));
    disp->setDisplay(_event.get());
    auto dispLoader = std::unique_ptr<IDisplayLoader>(new DisplayLoader(disp));
    setDisplayer(disp, dispLoader);
    initGame();
    run();
}

void    core::Bomberman::initGame()
{
    auto players = std::vector<std::unique_ptr<Player>>();
    players.push_back(std::make_unique<Player>(Player(ACharacter::Color::BLACK,
                                                      std::make_tuple(std::size_t(0), std::size_t(0)))));
    auto bots = std::vector<std::unique_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(std::make_tuple(std::size_t(0),
                                                             std::size_t(0)))));
    auto game = std::unique_ptr<AGame>(new Game(players, bots));
    loadGame("./../resources/maps/3", game);
}