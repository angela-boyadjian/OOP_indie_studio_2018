/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#include <algorithm>
#include <iostream>

#include "Bot.hpp"

bool            Bot::isBlock(const std::size_t &x, const std::size_t &y)
{
    return y > 0 and y < _transformedMap.size()
            and x > 0 and x < _transformedMap[y].size()
            and (_transformedMap[y][x] == '1'
            or _transformedMap[y][x] == '2');
}

std::size_t     Bot::countBlock()
{
    std::size_t count {0};
    std::size_t posX {std::get<0>(_pos)};
    std::size_t posY {std::get<1>(_pos)};

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
    std::size_t posX {std::get<0>(_pos)};
    std::size_t posY {std::get<1>(_pos)};

    return _transformedMap[posY][posX] == -1 or _transformedMap[posY][posX] == -2;
}

std::size_t Bot::getDistanceUp(std::size_t x, std::size_t y)
{
    std::size_t count {0};
    while (y > 0) {
        y -= 1;
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::size_t Bot::getDistanceDown(std::size_t x, std::size_t y)
{
    std::size_t count {0};
    while (y < _transformedMap.size()) {
        y += 1;
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::size_t Bot::getDistanceLeft(std::size_t x, std::size_t y)
{
    std::size_t count {0};
    while (x > 0) {
        x -= 1;
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::size_t Bot::getDistanceRight(std::size_t x, std::size_t y)
{
    std::size_t count {0};
    while (x < _transformedMap[y].size()) {
        x += 1;
        if (_transformedMap[y][x] == '0')
            return count;
        count += 1;
    }
    return 84;
}

std::vector<std::size_t> Bot::getDistancesToSurvive()
{
    auto    posX = std::get<0>(_pos);
    auto    posY = std::get<1>(_pos);
    return std::vector<std::size_t> {
        getDistanceUp(posX, posY),
        getDistanceDown(posX, posY),
        getDistanceLeft(posX, posY),
        getDistanceRight(posX, posY)
    };
}

ACharacter::Action  Bot::getOutOfDanger()
{
    std::size_t index {0};
    auto            distances = getDistancesToSurvive();
    auto    minElement = std::min_element(distances.begin(), distances.end());
    for (auto tmp {distances.begin()}; tmp != minElement; ++tmp)
        index += 1;
    return ACharacter::Action(index);
}

bool            Bot::isSafe(const std::size_t &x, const std::size_t &y)
{
    return y > 0 and y < _transformedMap.size()
        and x > 0 and x < _transformedMap[y].size()
        and _transformedMap[y][x] == '0';
}

ACharacter::Action  Bot::chooseDirection()
{
    std::vector<ACharacter::Action> directions;

    std::size_t posX {std::get<0>(_pos)};
    std::size_t posY {std::get<1>(_pos)};
    if (isSafe(posX, posY - 1))
        directions.push_back(ACharacter::Action::UP);
    if (isSafe(posX, posY + 1))
        directions.push_back(ACharacter::Action::DOWN);
    if (isSafe(posX - 1, posY))
        directions.push_back(ACharacter::Action::LEFT);
    if (isSafe(posX + 1, posY))
        directions.push_back(ACharacter::Action::RIGHT);
    return directions[rand() % directions.size()];
}

void    Bot::changePosition(const ACharacter::Action &a)
{
    if (a == ACharacter::Action::UP)
        std::get<2>(_pos) += 1;
    else if (a == ACharacter::Action::DOWN)
        std::get<2>(_pos) -= 1;
    else if (a == ACharacter::Action::LEFT)
        std::get<0>(_pos) -= 1;
    else if (a == ACharacter::Action::RIGHT)
        std::get<0>(_pos) += 1;
}

void    Bot::move(const std::vector<std::string> &, IDisplay *)
{
    _lastDirection = Action(rand() % 4);
    changePosition(_lastDirection);
    return;
    Action  a;
    if (_bombNumber == 0) {
        a = getOutOfDanger();
        changePosition(a);
    }
    else if (isMomentForBomb()) {
        std::cout << "Bomb Planted" << std::endl;
        a = ACharacter::Action::BOMB;
        _bombNumber -= 1;
    } else {
        a = chooseDirection();
        changePosition(a);
    }
    _lastDirection = a;
}