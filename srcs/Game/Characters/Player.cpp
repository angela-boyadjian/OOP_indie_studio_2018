/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(const std::size_t &enb, ACharacter::Color color, MapPos const &pos) :
    ACharacter(enb, pos, color)
{
    _action = ACharacter::Action::WAIT;
}

Player::~Player()
{
}

void    Player::moveUp()
{
    if (!_walls[0]) {
        std::get<1>(_pos) += 1;
        std::get<2>(_pos) += 1;
    }
}

void    Player::moveDown()
{
    if (!_walls[1]) {
        std::get<1>(_pos) -= 1;
        std::get<2>(_pos) -= 1;
    }
}

void    Player::moveLeft()
{
    if (!_walls[2])
        std::get<0>(_pos) -= 1;
}

void    Player::moveRight()
{
    if (!_walls[3])
        std::get<0>(_pos) += 1;
}

void    Player::isWallUp(IDisplay *d)
{
    std::get<2>(_pos) += 1;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[0] = d->isCollision(getEntityNb());
    std::get<2>(_pos) -= 1;
}

void    Player::isWallDown(IDisplay *d)
{
    std::get<2>(_pos) -= 1;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[1] = d->isCollision(getEntityNb());
    std::get<2>(_pos) += 1;
}


void    Player::isWallLeft(IDisplay *d)
{
    std::get<0>(_pos) -= 1;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[2] = d->isCollision(getEntityNb());
    std::get<0>(_pos) += 1;
}

void    Player::isWallRight(IDisplay *d)
{
    std::get<0>(_pos) += 1;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[3] = d->isCollision(getEntityNb());
    std::get<0>(_pos) -= 1;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
}

void    Player::isWalls(IDisplay *d)
{
    isWallUp(d);
    isWallDown(d);
    isWallLeft(d);
    isWallRight(d);
}

void    Player::move(const std::vector<std::string> &map, IDisplay *d)
{
    isWalls(d);
    switch (_action) {
        case ACharacter::Action::UP:
            moveUp();
            return;
        case ACharacter::Action::DOWN:
            moveDown();
            return;
        case ACharacter::Action::LEFT:
            moveLeft();
            return;
        case ACharacter::Action::RIGHT:
            moveRight();
            return;
        case ACharacter::Action::BOMB:
            decreaseBombNumber();
            d->destroyCollision(getEntityNb());
            return;
    }
}
