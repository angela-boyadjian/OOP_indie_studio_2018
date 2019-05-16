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
{}

core::Bomberman::~Bomberman()
{
}

// SETTERS
void core::Bomberman::setGame(std::unique_ptr<AGame> &g)
{
    _game = std::move(g);
}

void core::Bomberman::setDisplayer(std::unique_ptr<IDisplay> &d)
{
    _display = std::move(d);
    _dispLoader = DisplayLoader(_display);
}

void core::Bomberman::run()
{
    while (_display->isRunning())
        _display->draw();
}

void core::Bomberman::loadGame(const std::string &mapPath, std::unique_ptr<AGame> &game)
{
    auto map = std::unique_ptr<IMap>(new Map(mapPath));
    map->load();
    _game = std::move(game);
    _display->setCameraScene();
    _dispLoader.loadGame(_game);
    _dispLoader.loadMap(map->getMapData());
}