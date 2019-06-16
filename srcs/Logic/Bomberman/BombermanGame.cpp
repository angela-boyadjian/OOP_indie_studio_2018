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

std::vector<ACharacter::move_t> BombermanGame::moveBots(BombermanGame::Map &map, IDisplay *d)
{
    std::vector<ACharacter::move_t> actionVector;
    for (std::size_t i {0}; i < _bots.size(); ++i) {
        auto m = _bots[i]->move(map, d);
        actionVector.push_back(m);
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

std::vector<ACharacter::move_t> BombermanGame::movePlayers(const Event &events, Map &map,
        IDisplay *d)
{
    std::vector<ACharacter::move_t> actionVector;

    for (std::size_t i {0}; i < _players.size(); ++i) {
        auto action = pressKeyAction(events, i);
        _players[i]->setAction(action);
        auto m = _players[i]->move(map, d);
        _players[i]->setAction(ACharacter::Action::WAIT);
        actionVector.push_back(m);
    }
    return actionVector;
}