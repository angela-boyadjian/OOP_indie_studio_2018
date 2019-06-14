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

void    Player::takeBonus(std::vector<std::string> &map)
{
    auto b = map[std::get<1>(_2dPos)][std::get<0>(_2dPos)];
    if (b >= '7') {
        auto pu = PowerUp(b - 7 - 48);
        if (pu == PowerUp::FIRE_RANGE)
            increaseFireRange();
        else if (pu == PowerUp::BOMB) {
            _maxBombNumber += 1;
            increaseBombNumber();
        }
    }
}

ACharacter::move_t  Player::move(std::vector<std::string> &map, IDisplay *d)
{
    isWalls(d);
    takeBonus(map);
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
        case ACharacter::Action::BOMB:
            if (_bombNumber == 0)
                _action = ACharacter::Action::WAIT;
            _bombNumber -= 1;
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