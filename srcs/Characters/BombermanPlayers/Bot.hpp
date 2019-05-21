/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#pragma once

#include "ABombermanPlayer.hpp"

class Bot : public ABombermanPlayer {
public:
    // CONSTRUCTOR / DESTRUCTOR
    Bot(const std::size_t &enb, const MapPos &pos) : ABombermanPlayer(enb, pos),
    _lastDirection(ACharacter::Action::WAIT) {};
    ~Bot() = default;

    // BLOCKS
    std::size_t countBlock();
    bool        isBlock(const float &, const float &);

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
    void        move(const std::vector<std::string> &, IDisplay *) final;
    bool        isSafe(const float &, const float &);

    Action                      _lastDirection;
};