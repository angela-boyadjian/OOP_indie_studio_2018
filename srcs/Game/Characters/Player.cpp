/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"

static const char *res = "../resources/models/Character/Bomberman.MD3";

Player::Player(ACharacter::Color color, MapPos const &pos, Display &display) :
    ACharacter(pos), _display(display), _color(color)
{
}

Player::~Player()
{
}

void Player::loadPlayer()
{
    _display.addNewAnimation(res, _textures[static_cast<int>(_color)].c_str(),
        irr::core::vector3df(6, 6, 6));
}

void Player::displayPlayer()
{
    _display.draw();
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
