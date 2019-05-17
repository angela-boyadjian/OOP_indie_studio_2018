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
    Bot(const std::size_t &enb, const MapPos &pos) : ACharacter(enb, pos) {};
    ~Bot() = default;

    // BLOCKS
    std::size_t countBlock();
    bool        isBlock(const std::size_t &, const std::size_t &);

    // SURVIVE
    bool        isInDanger();
    Action      getOutOfDanger();
    std::size_t getDistanceUp(std::size_t, std::size_t);
    std::size_t getDistanceDown(std::size_t, std::size_t);
    std::size_t getDistanceLeft(std::size_t, std::size_t);
    std::size_t getDistanceRight(std::size_t, std::size_t);
    std::vector<std::size_t> getDistancesToSurvive();

    // BOMB
    bool        isMomentForBomb();

    // MOVE
    Action      chooseDirection();
    void        changePosition(const Action &);
    void        move(const std::vector<std::string> &) final;
    bool        isSafe(const std::size_t &, const std::size_t &);

    Action                      _lastDirection;
private:
    std::vector<std::string>    _transformedMap;
};