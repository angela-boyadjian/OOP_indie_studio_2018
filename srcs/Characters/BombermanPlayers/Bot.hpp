/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#pragma once

#include <chrono>
#include "ABombermanPlayer.hpp"

class Bot : public ABombermanPlayer {
public:
    // CONSTRUCTOR / DESTRUCTOR
    Bot(const std::size_t &enb, ACharacter::Color color, const MapPos &pos) : ABombermanPlayer(enb, pos, color),
        _c(std::chrono::system_clock::now()), _lastDirection(ACharacter::Action::WAIT), _movement(0) {};
    ~Bot() = default;

    // BLOCKS
    std::size_t countBlock(std::vector<std::string> &);
    bool        isBlock(const float &, const float &, std::vector<std::string> &);

    // SURVIVE
    bool        isInDanger(std::vector<std::string> &);
    Action      getOutOfDanger(std::vector<std::string> &);
    std::size_t getDistanceUp(float, float, std::vector<std::string> &);
    std::size_t getDistanceDown(float, float, std::vector<std::string> &);
    std::size_t getDistanceLeft(float, float, std::vector<std::string> &);
    std::size_t getDistanceRight(float, float, std::vector<std::string> &);
    std::vector<std::size_t> getDistancesToSurvive(std::vector<std::string> &);

    // BOMB
    bool        isMomentForBomb(std::vector<std::string> &);
    void        bombExplosion(std::vector<std::string> &);
    void        putBomb(std::vector<std::string> &);

    // MOVE
    bool    takeBonus(std::vector<std::string> &);
    bool    goToBonus(std::vector<std::string> &);
    void    otherMove(std::vector<std::string> &);
    std::tuple<bool, std::size_t>   isPowerUp(std::vector<std::string> &, const int &, const int &);
    std::tuple<bool, std::size_t>   isPowerDown(std::vector<std::string> &, const int &, const int &);
    std::tuple<bool, std::size_t>   isPowerLeft(std::vector<std::string> &, const int &, const int &);
    std::tuple<bool, std::size_t>   isPowerRight(std::vector<std::string> &, const int &, const int &);
    std::tuple<bool, ACharacter::Action>    isPower(std::vector<std::string> &);
    Action      chooseDirection(std::vector<std::string> &);
    void        changePosition(const Action &);
    move_t      move(std::vector<std::string> &, IDisplay *) final;
    bool        isSafe(const float &, const float &, std::vector<std::string> &);
    void        animation();

    std::chrono::time_point<std::chrono::system_clock> _c;
    Action                      _lastDirection;
    std::size_t                 _movement;
};