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
            std::get<1>(_pos) -= 1;
        case ACharacter::Action::DOWN:
            std::get<1>(_pos) += 1;
        case ACharacter::Action::LEFT:
            std::get<0>(_pos) -= 1;
        case ACharacter::Action::RIGHT:
            std::get<0>(_pos) += 1;
        case ACharacter::Action::BOMB:
            decreaseBombNumber();
        default:
            return;
    }
}
