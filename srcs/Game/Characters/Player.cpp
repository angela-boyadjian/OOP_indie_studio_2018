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

void    Player::up()
{
    if (!_walls[0] && !(_walls[2] || _walls[3])) {
        std::get<1>(_pos) += 1;
        std::get<2>(_pos) += 1;
    }
}

void    Player::down()
{
    if (!_walls[1] && !(_walls[2] || _walls[3])) {
        std::get<1>(_pos) -= 1;
        std::get<2>(_pos) -= 1;
    }
}

void    Player::left()
{
    if (!_walls[2] && !(_walls[0] || _walls[1]))
        std::get<0>(_pos) -= 1;
}

void    Player::right()
{
    if (!_walls[3] && !(_walls[0] || _walls[1]))
        std::get<0>(_pos) += 1;
}

void    Player::isWalls(IDisplay *d)
{
    std::get<2>(_pos) += 1;
    _walls[0] = d->isCollision(getEntityNb());
    std::get<2>(_pos) -= 1;

    std::get<2>(_pos) -= 1;
    _walls[1] = d->isCollision(getEntityNb());
    std::get<2>(_pos) += 1;

    std::get<0>(_pos) -= 1;
    _walls[2] = d->isCollision(getEntityNb());
    std::get<0>(_pos) += 1;

    std::get<0>(_pos) += 1;
    _walls[3] = d->isCollision(getEntityNb());
    std::get<0>(_pos) -= 1;
}

void    Player::move(const std::vector<std::string> &map, IDisplay *d)
{
    isWalls(d);
    switch (_action) {
        case ACharacter::Action::UP:
            up();
            return;
        case ACharacter::Action::DOWN:
            down();
            return;
        case ACharacter::Action::LEFT:
            left();
            return;
        case ACharacter::Action::RIGHT:
            right();
            return;
        case ACharacter::Action::BOMB:
            decreaseBombNumber();
            return;
        default:
            return;
    }
}
