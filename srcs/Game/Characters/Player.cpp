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

void Player::move(const std::vector<std::string> &map, IDisplay *d)
{
    switch (_action) {
        case ACharacter::Action::UP:
            std::get<1>(_pos) += 10;
            std::get<2>(_pos) += 10;
            if (d->isCollision(getEntityNb())) {
                std::get<1>(_pos) -= 10;
                std::get<2>(_pos) -= 10;
            } else {
                std::get<1>(_pos) -= 9;
                std::get<2>(_pos) -= 9;
            }
            return;
        case ACharacter::Action::DOWN:
            std::get<1>(_pos) -= 10;
            std::get<2>(_pos) -= 10;
            if (d->isCollision(getEntityNb())) {
                std::get<1>(_pos) += 10;
                std::get<2>(_pos) += 10;
            } else {
                std::get<1>(_pos) += 9;
                std::get<2>(_pos) += 9;
            }
            return;
        case ACharacter::Action::LEFT:
            std::get<0>(_pos) -= 10;
            if (d->isCollision(getEntityNb()))
                std::get<0>(_pos) += 10;
            else
                std::get<0>(_pos) += 9;
            return;
        case ACharacter::Action::RIGHT:
            std::get<0>(_pos) += 10;
            if (d->isCollision(getEntityNb()))
                std::get<0>(_pos) -= 10;
            else
                std::get<0>(_pos) -= 9;
            return;
        case ACharacter::Action::BOMB:
            decreaseBombNumber();
            return;
        default:
            return;
    }
}
