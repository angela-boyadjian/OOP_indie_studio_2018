/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#pragma once

#include <tuple>
#include <vector>
#include <string>

class ACharacter {
public:
    using MapPos = std::tuple<std::size_t, std::size_t>;

    // DIRECTION OF THE CHARACTER
    enum class Action {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        BOMB,
        WAIT
    };

    enum class Color {
        BLACK,
        PINK,
        RED,
        WHITE
    };

    // CONSTRUCTOR / DESTRUCTOR
    ACharacter(const MapPos &);
    ~ACharacter() = default;

    // GETTERS
    const MapPos        &getMapPos() const;
    const std::size_t   &getFireRange() const;
    const Action        &getDirection() const;

    // INCREASER
    void    increaseSpeed();
    void    increaseFireRange();
    void    increaseBombNumber();

    // DEPLACEMENT
    virtual void    move(const std::vector<std::string> &) = 0;
public:
    std::vector<std::string>    _textures;
protected:
    MapPos                      _pos;
    std::size_t                 _speed;
    Action                      _action;
    std::size_t                 _fireRange;
    std::size_t                 _bombNumber;
    std::size_t                 _maxBombNumber;
};
