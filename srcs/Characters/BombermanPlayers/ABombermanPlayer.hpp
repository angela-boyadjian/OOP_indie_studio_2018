/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ABombermanPlayer
*/

#pragma once

#include "ACharacter.hpp"

class ABombermanPlayer : public ACharacter {
public:
    explicit ABombermanPlayer(const std::size_t &, const MapPos &,
            const Color & = ACharacter::Color::PINK);
    ~ABombermanPlayer() = default;
    virtual void    move(const std::vector<std::string> &, IDisplay *) = 0;

    // GETTERS
    const bool          &canShoot() const;
    const std::size_t   &getFireRange() const;
    const Action        &getDirection() const;

    // INCREASER
    void    increaseSpeed();
    void    increaseFireRange();
    void    increaseBombNumber();

    // DECREASER
    void    decreaseBombNumber();

    // SETTERS
    void    canShoot();

    // NOTE MOVE
    void    moveUp();
    void    moveDown();
    void    moveLeft();
    void    moveRight();

    // WALL
    void    isWallUp(IDisplay *);
    void    isWallDown(IDisplay *);
    void    isWallLeft(IDisplay *);
    void    isWallRight(IDisplay *);
    void    isWalls(IDisplay *);

    void    bomb(IDisplay *);
protected:
    bool        _walls[4];
    bool        _canShoot;
    std::size_t _fireRange;
    std::size_t _bombNumber;
    std::size_t _maxBombNumber;
};