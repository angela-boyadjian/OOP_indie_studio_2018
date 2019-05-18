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

std::vector<ACharacter::Action> Game::moveBots(const Game::Map &map)
{
    std::vector<ACharacter::Action> actionVector;
    for (std::size_t i {0}; i < _bots.size(); ++i) {
        _bots[i]->move(map);
        actionVector.push_back(_bots[i]->_lastDirection);
    }
    return actionVector;
}

std::vector<ACharacter::Action> Game::movePlayers(const Event &events, const Map &map)
{
    std::vector<ACharacter::Action> actionVector;
    ACharacter::Action  tmp = ACharacter::Action::WAIT;

    for (std::size_t i {0}; i < _players.size(); ++i) {
        if (events->IsKeyDown(_players[i]->getKeyMap()["UP"]))
            tmp = ACharacter::Action::UP;
        else if (events->IsKeyDown(_players[i]->getKeyMap()["DOWN"]))
            tmp = ACharacter::Action::DOWN;
        else if (events->IsKeyDown(_players[i]->getKeyMap()["LEFT"]))
            tmp = ACharacter::Action::LEFT;
        else if (events->IsKeyDown(_players[i]->getKeyMap()["RIGHT"]))
            tmp = ACharacter::Action::RIGHT;
        else if (events->IsKeyDown(_players[i]->getKeyMap()["BOMB"]))
            tmp = ACharacter::Action::BOMB;
        _players[i]->setAction(tmp);
        _players[i]->move(map);
        _players[i]->setAction(ACharacter::Action::WAIT);
        actionVector.push_back(tmp);
    }
    return actionVector;
}