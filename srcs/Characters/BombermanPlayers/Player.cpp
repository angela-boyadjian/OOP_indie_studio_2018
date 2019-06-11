/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(const std::size_t &enb, ACharacter::Color color, MapPos const &pos) :
    ABombermanPlayer(enb, pos, color)
{
    _action = ACharacter::Action::WAIT;
}

Player::~Player()
{
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
            bomb(d);
            return;
        case ACharacter::Action::WAIT:
            return;
    }
}