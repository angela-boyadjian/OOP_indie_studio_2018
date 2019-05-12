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
    if (y > 0 and y < _transformedMap.size()
            and x > 0 and x < _transformedMap[y].size()
            and (_transformedMap[y][x] == '1'
            or _transformedMap[y][x] == '2'))
        return true;
    return false;
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
    if (_bombNumber > 0 and countBlock() >= 2)
        return false;
    else
        return true;
}

bool            Bot::isInDanger()
{
    std::size_t posX {std::get<0>(_pos)};
    std::size_t posY {std::get<1>(_pos)};

    if (_transformedMap[posY][posX] == '-1'
            or _transformedMap[posY][posX] == '-2')
        return true;
    return false;
}

// TO IMPLEMENT
std::size_t     Bot::getDistanceToSurvive(const ACharacter::Action &)
{
    std::size_t count {0};
    std::size_t posX {std::get<0>(_pos)};
    std::size_t posY {std::get<1>(_pos)};
    return 0;
}

ACharacter::Action  Bot::getOutOfDanger()
{
    std::size_t index {0};
    std::vector<std::size_t>    distances {
        getDistanceToSurvive(ACharacter::Action::UP),
        getDistanceToSurvive(ACharacter::Action::DOWN),
        getDistanceToSurvive(ACharacter::Action::LEFT),
        getDistanceToSurvive(ACharacter::Action::RIGHT)
    };
    auto    minElement = std::min_element(distances.begin(), distances.end());
    for (auto tmp {distances.begin()}; tmp != minElement; ++tmp)
        index += 1;
    return ACharacter::Action(index);
}

bool            Bot::isSafe(const std::size_t &x, const std::size_t &y)
{
    if (y > 0 and y < _transformedMap.size()
        and x > 0 and x < _transformedMap[y].size()
        and _transformedMap[y][x] == '0')
        return true;
    return false;
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
        std::get<1>(_pos) -= 1;
    else if (a == ACharacter::Action::DOWN)
        std::get<1>(_pos) += 1;
    else if (a == ACharacter::Action::LEFT)
        std::get<0>(_pos) -= 1;
    else if (a == ACharacter::Action::RIGHT)
        std::get<0>(_pos) += 1;
}

void    Bot::move(const std::vector<std::string> &)
{
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