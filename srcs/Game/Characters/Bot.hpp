/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#pragma once

#include "ACharacter.hpp"

class Bot : public ACharacter {
public:
    // CONSTRUCTOR / DESTRUCTOR
    Bot(const MapPos &pos) : ACharacter(pos) {};
    ~Bot() = default;

    // BLOCKS
    std::size_t countBlock();
    bool        isBlock(const std::size_t &, const std::size_t &);

    // SURVIVE
    bool        isInDanger();
    Action      getOutOfDanger();
    std::size_t getDistanceToSurvive(const Action &);

    // BOMB
    bool        isMomentForBomb();

    // MOVE
    bool        isSafe(const std::size_t &, const std::size_t &);
    Action      getDirection();
    Action      chooseDirection();
    void        changePosition(const Action &);
    void        move(const std::vector<std::string> &);

private:
    Action                      _lastDirection;
    std::vector<std::string>    _transformedMap;
};