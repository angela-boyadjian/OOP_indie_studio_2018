/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/
#pragma once

#include <tuple>
#include <vector>

class ACharacter {
public:
    using MapPos = std::tuple<std::size_t, std::size_t>;

    // NOTE DIRECTION OF THE CHARACTER
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum class Color {
        BLACK,
        PINK,
        RED,
        WHITE
    };

    // NOTE CONSTRUCTOR / DESTRUCTOR
    ACharacter(const MapPos &);
    ~ACharacter() = default;

    // GETTERS
    const MapPos        &getMapPos() const;
    const std::size_t   &getFireRange() const;
    const Direction     &getDirection() const;

    // NOTE INCREASER
    void    increaseSpeed();
    void    increaseFireRange();
    void    increaseBombNumber();

    // NOTE MOVE
    virtual void    move() = 0;
public:
    std::vector<std::string>    _textures;
private:
    MapPos                      _pos;
    std::size_t                 _speed;
    Direction                   _direction;
    std::size_t                 _fireRange;
    std::size_t                 _bombNumber;
    std::size_t                 _maxBombNumber;
};
