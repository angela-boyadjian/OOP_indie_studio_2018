/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "Bot.hpp"

bool            Bot::isBlock(const float &x, const float &y)
{
    return y >= 0 and y < _transformedMap.size()
            and x >= 0 and x < _transformedMap[y].size()
            and (_transformedMap[y][x] == '1'
            or _transformedMap[y][x] == '2');
}

std::size_t     Bot::countBlock()
{
    std::size_t count {0};
    auto        posX {std::get<0>(_pos)};
    auto    posY {(std::get<2>(_pos) * -1 / 10) + 3};

    if (isBlock(posX, posY + 1))
        ++count;
    if (isBlock(posX, posY - 1))
        ++count;
    if (isBlock(posX + 1, posY))
        ++count;
    if (isBlock(posX - 1, posY))
        ++count;
    return count;
}

bool            Bot::isMomentForBomb()
{
    return _bombNumber > 0 and countBlock() >= 2;
}

bool            Bot::isInDanger()
{
    auto    posX {std::get<0>(_pos)};
    auto    posY {(std::get<2>(_pos) * -1 / 10) + 3};
    return _transformedMap[posY][posX] == -1 or _transformedMap[posY][posX] == -2;
}

std::size_t Bot::getDistanceUp(float x, float y)
{
    std::size_t count {0};
    while (--y > 0) {
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::size_t Bot::getDistanceDown(float x, float y)
{
    std::size_t count {0};
    while (++y < _transformedMap.size()) {
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::size_t Bot::getDistanceLeft(float x, float y)
{
    std::size_t count {0};
    while (--x > 0) {
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::size_t Bot::getDistanceRight(float x, float y)
{
    std::size_t count {0};
    while (++x < _transformedMap[y].size()) {
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::vector<std::size_t> Bot::getDistancesToSurvive()
{
    auto    posX = std::get<0>(_pos);
    auto    posY {(std::get<2>(_pos) * -1 / 10) + 3};

    return std::vector<std::size_t> {
        getDistanceUp(posX, posY),
        getDistanceDown(posX, posY),
        getDistanceLeft(posX, posY),
        getDistanceRight(posX, posY)
    };
}

ACharacter::Action  Bot::getOutOfDanger()
{
    std::size_t     index {0};
    auto            distances = getDistancesToSurvive();
    auto            minElement = std::min_element(distances.begin(), distances.end());
    for (auto tmp {distances.begin()}; tmp != minElement; ++tmp)
        index += 1;
    return ACharacter::Action(index);
}

bool            Bot::isSafe(const float &x, const float &y)
{
    return y >= 0 and y < _transformedMap.size()
        and x >= 0 and x < _transformedMap[y].size()
        and _transformedMap[y][x] == '0';
}

ACharacter::Action  Bot::chooseDirection()
{
    std::vector<ACharacter::Action> directions;
    auto    posX {std::get<0>(_pos)};
    auto    posY {(std::get<2>(_pos) * -1 / 10) + 3};

    if (isSafe(posX, posY - 1))
        directions.push_back(ACharacter::Action::UP);
    if (isSafe(posX, posY + 1))
        directions.push_back(ACharacter::Action::DOWN);
    if (isSafe(posX - 1, posY))
        directions.push_back(ACharacter::Action::LEFT);
    if (isSafe(posX + 1, posY))
        directions.push_back(ACharacter::Action::RIGHT);
    auto randDirection = std::rand() / (RAND_MAX + directions.size());
    return directions.empty() ? ACharacter::Action::WAIT : directions[randDirection];
}

void    Bot::changePosition(const ACharacter::Action &a)
{
    if (a == ACharacter::Action::UP)
        std::get<2>(_pos) += 10;
    else if (a == ACharacter::Action::DOWN)
        std::get<2>(_pos) -= 10;
    else if (a == ACharacter::Action::LEFT)
        std::get<0>(_pos) -= 10;
    else if (a == ACharacter::Action::RIGHT)
        std::get<0>(_pos) += 10;
}

std::vector<std::string> tmp_map = {
        "0022222222200",
        "0121212121210",
        "2222222222222",
        "2121212121212",
        "2222222222222",
        "2121212121212",
        "2222222222222",
        "2121212121212",
        "2222222222222",
        "0121212121210",
        "0022222222200"
};

void    Bot::bombExplosion()
{
    for (auto j {0}; j < _transformedMap.size(); ++j) {
        for (auto i = 0; i < _transformedMap[j].size(); ++i) {
            if (_transformedMap[j][i] == '4') {
                _transformedMap[j][i] = '0';
                if (j > 0 and (_transformedMap[j - 1][i] == '3' or _transformedMap[j - 1][i] == '2'))
                    _transformedMap[j - 1][i] = '0';
                if (j < _transformedMap.size() and (_transformedMap[j + 1][i] == '3' or _transformedMap[j + 1][i] == '2'))
                    _transformedMap[j + 1][i] = '0';
                if (i > 0 and (_transformedMap[j][i - 1] == '3' or _transformedMap[j][i - 1] == '2'))
                    _transformedMap[j][i - 1] = '0';
                if (i < _transformedMap[j].size() and (_transformedMap[j][i + 1] == '3' or _transformedMap[j][i + 1] == '2'))
                    _transformedMap[j][i + 1] = '0';
            }
        }
    }
}

void    Bot::putBomb()
{
    auto    posX {std::get<0>(_pos)};
    auto    posY {(std::get<2>(_pos) * -1 / 10) + 3};

    _transformedMap[posY][posX] = '4';
    if (posY > 0 and _transformedMap[posY - 1][posX] != '1'
            and _transformedMap[posY - 1][posX] != '2')
        _transformedMap[posY - 1][posX] = '3';

    if (posY < _transformedMap.size() and _transformedMap[posY + 1][posX] != '1'
            and _transformedMap[posY + 1][posX] != '2')
        _transformedMap[posY + 1][posX] = '3';

    if (posX > 0 and _transformedMap[posY][posX - 1] != '1'
            and _transformedMap[posY][posX - 1] != '2')
        _transformedMap[posY][posX - 1] = '3';

    if (posX < _transformedMap[posY].size() and _transformedMap[posY][posX + 1] != '1'
            and _transformedMap[posY][posX + 1] != '2')
        _transformedMap[posY][posX + 1] = '3';
}

void    Bot::move(const std::vector<std::string> &map, IDisplay *d)
{
    static bool flag = true;
    auto count {0};
    if (flag) {
        _transformedMap = tmp_map;
        flag = false;
    }
    Action  a;
    if (_bombNumber == 0 && count % 100 == 0) {
        _bombNumber += 1;
        bombExplosion();
    }
    if (_bombNumber == 0) {
        a = getOutOfDanger();
        changePosition(a);
    } else if (isMomentForBomb()) {
        a = ACharacter::Action::BOMB;
        putBomb();
        decreaseBombNumber();
    } else {
        a = chooseDirection();
        changePosition(a);
    }
    _lastDirection = a;
    ++count;
}