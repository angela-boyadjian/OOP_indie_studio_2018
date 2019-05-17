/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"


Player::Player(ACharacter::Color color, MapPos const &pos) :
    ACharacter(pos, color)
{
    _action = ACharacter::Action::WAIT;
}

Player::~Player()
{
}

void Player::displayPlayer()
{
}

void Player::move(const std::vector<std::string> &map)
{
    switch (_action) {
        case ACharacter::Action::UP:
            std::get<1>(_pos) += 1;
            return;
        case ACharacter::Action::DOWN:
            std::get<1>(_pos) -= 1;
            return;
        case ACharacter::Action::LEFT:
            std::get<0>(_pos) -= 1;
            return;
        case ACharacter::Action::RIGHT:
            std::get<0>(_pos) += 1;
            return;
        case ACharacter::Action::BOMB:
            decreaseBombNumber();
            return;
        default:
            return;
    }
}
