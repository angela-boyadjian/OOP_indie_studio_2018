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
    _lastDirection(ACharacter::Action::WAIT) { _2dPos = std::make_tuple(0, 10); };
    ~Bot() = default;

    // BLOCKS
    std::size_t countBlock();
    bool        isBlock(const float &, const float &);

    // SURVIVE
    bool        isInDanger();
    Action      getOutOfDanger();
    std::size_t getDistanceUp(float, float);
    std::size_t getDistanceDown(float, float);
    std::size_t getDistanceLeft(float, float);
    std::size_t getDistanceRight(float, float);
    std::vector<std::size_t> getDistancesToSurvive();

    // BOMB
    bool        isMomentForBomb();
    void        bombExplosion();
    void        putBomb();

    // MOVE
    Action      chooseDirection();
    void        changePosition(const Action &);
    void        move(std::vector<std::string> &, IDisplay *) final;
    bool        isSafe(const float &, const float &);

    Action                      _lastDirection;
};