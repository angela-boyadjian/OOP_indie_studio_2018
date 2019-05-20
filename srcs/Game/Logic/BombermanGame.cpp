/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#include "BombermanGame.hpp"

BombermanGame::BombermanGame(Players &p, Bots &b) : AGame(p, b)
{
}

std::vector<ACharacter::Action> BombermanGame::moveBots(const BombermanGame::Map &map, IDisplay *d)
{
    std::vector<ACharacter::Action> actionVector;
    for (std::size_t i {0}; i < _bots.size(); ++i) {
        _bots[i]->move(map, d);
        actionVector.push_back(_bots[i]->_lastDirection);
    }
    return actionVector;
}

ACharacter::Action  BombermanGame::pressKeyAction(const AGame::Event &events, const std::size_t &i)
{
    ACharacter::Action  action = ACharacter::Action::WAIT;

    if (events->IsKeyDown(_players[i]->getKeyMap()["UP"]))
        action = ACharacter::Action::UP;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["DOWN"]))
        action = ACharacter::Action::DOWN;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["LEFT"]))
        action = ACharacter::Action::LEFT;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["RIGHT"]))
        action = ACharacter::Action::RIGHT;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["BOMB"]))
        action = ACharacter::Action::BOMB;
    return action;
}

std::vector<ACharacter::Action> BombermanGame::movePlayers(const Event &events, const Map &map,
        IDisplay *d)
{
    std::vector<ACharacter::Action> actionVector;

    for (std::size_t i {0}; i < _players.size(); ++i) {
        auto action = pressKeyAction(events, i);
        _players[i]->setAction(action);
        _players[i]->move(map, d);
        _players[i]->setAction(ACharacter::Action::WAIT);
        actionVector.push_back(action);
    }
    return actionVector;
}