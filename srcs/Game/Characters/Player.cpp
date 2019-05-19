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

void    Player::up(IDisplay *d)
{
    std::get<1>(_pos) += 1;
    std::get<2>(_pos) += 1;
    if (d->isCollision(getEntityNb())) {
        std::get<1>(_pos) -= 1;
        std::get<2>(_pos) -= 1;
    }
}

void    Player::down(IDisplay *d)
{
    std::get<1>(_pos) -= 1;
    std::get<2>(_pos) -= 1;
    if (d->isCollision(getEntityNb())) {
        std::get<1>(_pos) += 1;
        std::get<2>(_pos) += 1;
    }
}

void    Player::left(IDisplay *d)
{
    std::get<0>(_pos) -= 1;
    if (d->isCollision(getEntityNb()))
        std::get<0>(_pos) += 1;
}

void    Player::right(IDisplay *d)
{
    std::get<0>(_pos) += 1;
    if (d->isCollision(getEntityNb()))
        std::get<0>(_pos) -= 1;
}

void    Player::move(const std::vector<std::string> &map, IDisplay *d)
{
    switch (_action) {
        case ACharacter::Action::UP:
            up(d);
            return;
        case ACharacter::Action::DOWN:
            down(d);
            return;
        case ACharacter::Action::LEFT:
            left(d);
            return;
        case ACharacter::Action::RIGHT:
            right(d);
            return;
        case ACharacter::Action::BOMB:
            decreaseBombNumber();
            return;
        default:
            return;
    }
}
