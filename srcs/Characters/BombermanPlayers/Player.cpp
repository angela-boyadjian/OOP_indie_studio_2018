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
    createKeyMap(_entityNb);
}

Player::~Player()
{
}

void    Player::getFirstKeyMap()
{
    _keyMap["UP"] = irr::EKEY_CODE::KEY_KEY_Z;
    _keyMap["DOWN"] = irr::EKEY_CODE::KEY_KEY_S;
    _keyMap["LEFT"] = irr::EKEY_CODE::KEY_KEY_Q;
    _keyMap["RIGHT"] = irr::EKEY_CODE::KEY_KEY_D;
    _keyMap["BOMB"] = irr::EKEY_CODE::KEY_KEY_C;
}

void    Player::getSecondKeyMap()
{
    _keyMap["UP"] = irr::EKEY_CODE::KEY_KEY_T;
    _keyMap["DOWN"] = irr::EKEY_CODE::KEY_KEY_G;
    _keyMap["LEFT"] = irr::EKEY_CODE::KEY_KEY_F;
    _keyMap["RIGHT"] = irr::EKEY_CODE::KEY_KEY_H;
    _keyMap["BOMB"] = irr::EKEY_CODE::KEY_KEY_B;
}

void    Player::getThirdKeyMap()
{
    _keyMap["UP"] = irr::EKEY_CODE::KEY_UP;
    _keyMap["DOWN"] = irr::EKEY_CODE::KEY_DOWN;
    _keyMap["LEFT"] = irr::EKEY_CODE::KEY_LEFT;
    _keyMap["RIGHT"] = irr::EKEY_CODE::KEY_RIGHT;
    _keyMap["BOMB"] = irr::EKEY_CODE::KEY_SPACE;
}

void    Player::getFourthKeyMap()
{
    _keyMap["UP"] = irr::EKEY_CODE::KEY_UP;
    _keyMap["DOWN"] = irr::EKEY_CODE::KEY_DOWN;
    _keyMap["LEFT"] = irr::EKEY_CODE::KEY_LEFT;
    _keyMap["RIGHT"] = irr::EKEY_CODE::KEY_RIGHT;
    _keyMap["BOMB"] = irr::EKEY_CODE::KEY_SPACE;
}

void    Player::createKeyMap(const std::size_t &i)
{
    switch (i) {
        case 0:
            getFirstKeyMap();
            break;
        case 1:
            getSecondKeyMap();
            break;
        case 2:
            getThirdKeyMap();
            break;
        case 3:
            getFourthKeyMap();
            break;
        default:
            break;
    }
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
    auto b = map[std::get<1>(_2dPos)][std::get<0>(_2dPos)];
    if (b >= '7') {
        auto pu = PowerUp(b - 7 - 48);
        if (pu == PowerUp::FIRE_RANGE)
            increaseFireRange();
        else if (pu == PowerUp::BOMB) {
            _maxBombNumber += 1;
            increaseBombNumber();
        }
        map[std::get<1>(_2dPos)][std::get<0>(_2dPos)] = '0';
    }
}

ACharacter::move_t  Player::move(std::vector<std::string> &map, IDisplay *d)
{
    isWalls(d);
    takeBonus(map);
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
    return { .x = std::get<0>(_2dPos), .y = std::get<1>(_2dPos), .action = _action, .itself = this};
}