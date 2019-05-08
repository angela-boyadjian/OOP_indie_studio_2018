#pragma once

#include <tuple>

using MapPos = std::tuple<std::size_t, std::size_t>;

class ACharacter {
public:
    // DIRECTION OF THE CHARACTER
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // CONSTRUCTOR / DESTRUCTOR
    ACharacter(const MapPos &);
    ~ACharacter() = default;

    // GETTERS
    const MapPos        &getMapPos() const;
    const std::size_t   &getFireRange() const;
    const Direction     &getDirection() const;

    // INCREASER
    void    increaseSpeed();
    void    increaseFireRange();
    void    increaseBombNumber();

    // DEPLACEMENTS
    virtual void    move() = 0;

private:
    MapPos          _pos;
    std::size_t     _speed;
    Direction       _direction;
    std::size_t     _fireRange;
    std::size_t     _bombNumber;
    std::size_t     _maxBombNumber;
};