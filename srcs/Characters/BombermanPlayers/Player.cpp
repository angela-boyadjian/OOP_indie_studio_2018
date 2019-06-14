/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include <unistd.h>
#include "Player.hpp"

Player::Player(const std::size_t &enb, ACharacter::Color color, MapPos const &pos) :
    ABombermanPlayer(enb, pos, color)
{
    _action = ACharacter::Action::WAIT;
    _2dPos = std::make_tuple(0, 0);
}

Player::~Player()
{
}

ACharacter::move_t  Player::move(std::vector<std::string> &map, IDisplay *d)
{
    isWalls(d);
    map[std::get<1>(_2dPos)][std::get<0>(_2dPos)] = '0';
    switch (_action) {
        case ACharacter::Action::UP:
            moveUp();
            break;
        case ACharacter::Action::DOWN:
            moveDown();
            break;
        case ACharacter::Action::LEFT:
            moveLeft();
            break;
        case ACharacter::Action::RIGHT:
            moveRight();
            break;
        default:
            break;
    }
    map.at(std::get<1>(_2dPos)).at(std::get<0>(_2dPos)) = '4';
    for (auto &m : map)
        std::cout << m << std::endl;
    std::cout << std::endl;
    return { .x = std::get<0>(_2dPos), .y = std::get<1>(_2dPos), .action = _action, .itself = this};
}