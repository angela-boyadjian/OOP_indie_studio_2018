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
}

Player::~Player()
{
}

void    Player::putBomb(std::vector<std::string> &map)
{
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    map[posY][posX] = '5';
    for (auto i {1}; i < _fireRange + 1; ++i) {
        if (posY - i >= 0 and map[posY - i][posX] != '1'
            and map[posY - i][posX] != '2')
            map[posY - i][posX] = '3';

        if (posY + i < map.size() and map[posY + i][posX] != '1'
            and map[posY + i][posX] != '2')
            map[posY + i][posX] = '3';

        if (posX - i >= 0 and map[posY][posX - i] != '1'
            and map[posY][posX - i] != '2')
            map[posY][posX - i] = '3';

        if (posX + i < map[posY].size() and map[posY][posX + i] != '1'
            and map[posY][posX + i] != '2')
            map[posY][posX + i] = '3';
    }
}

void    Player::takeBonus(std::vector<std::string> &map)
{
    std::cout << "posX = " << std::get<0>(_2dPos) << std::endl;
    std::cout << "posY = " << std::get<1>(_2dPos) << std::endl;
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
    if (map[std::get<1>(_2dPos)][std::get<0>(_2dPos)] != '3'
        and map[std::get<1>(_2dPos)][std::get<0>(_2dPos)] != '5')
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
            else {
                putBomb(map);
                _bombNumber -= 1;
            }
            break;
        default:
            break;
    }
//    map.at(std::get<1>(_2dPos)).at(std::get<0>(_2dPos)) = '4';
//    for (auto &m : map)
//        std::cout << m << std::endl;
//    std::cout << std::endl;
    return { .x = std::get<0>(_2dPos), .y = std::get<1>(_2dPos), .action = _action, .itself = this};
}