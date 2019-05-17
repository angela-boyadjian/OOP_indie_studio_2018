/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#include "Game.hpp"

Game::Game(Players &p, Bots &b) : AGame(p, b)
{
}

void    Game::moveBots(const Game::Map &map)
{
    for (std::size_t i {0}; i < _bots.size(); ++i)
        _bots[i]->move(map);
}

void    Game::movePlayers(const Event &events, const Map &map)
{
    for (std::size_t i {0}; i < _players.size(); ++i) {
        if (events->IsKeyDown(_players[i]->getKeyMap()["UP"]))
            _players[i]->setAction(ACharacter::Action::UP);
        else if (events->IsKeyDown(_players[i]->getKeyMap()["DOWN"]))
            _players[i]->setAction(ACharacter::Action::DOWN);
        else if (events->IsKeyDown(_players[i]->getKeyMap()["LEFT"]))
            _players[i]->setAction(ACharacter::Action::LEFT);
        else if (events->IsKeyDown(_players[i]->getKeyMap()["RIGHT"]))
            _players[i]->setAction(ACharacter::Action::RIGHT);
        else if (events->IsKeyDown(_players[i]->getKeyMap()["BOMB"]))
            _players[i]->setAction(ACharacter::Action::BOMB);
        _players[i]->move(map);
        _players[i]->setAction(ACharacter::Action::WAIT);
    }
}