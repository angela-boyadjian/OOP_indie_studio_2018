/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <chrono>

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
    auto        posX {std::get<0>(_2dPos)};
    auto        posY {std::get<1>(_2dPos)};

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
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};
    return _transformedMap[posY][posX] == -1 or _transformedMap[posY][posX] == -2;
}

std::size_t Bot::getDistanceUp(float x, float y)
{
    std::size_t count {0};
    while (--y >= 0) {
        if (_transformedMap[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::size_t Bot::getDistanceDown(float x, float y)
{
    std::size_t count {0};
    while (++y < _transformedMap.size()) {
        if (_transformedMap[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::size_t Bot::getDistanceLeft(float x, float y)
{
    std::size_t count {0};
    while (--x >= 0) {
        if (_transformedMap[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::size_t Bot::getDistanceRight(float x, float y)
{
    std::size_t count {0};
    while (++x < _transformedMap[y].size()) {
        if (_transformedMap[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::vector<std::size_t> Bot::getDistancesToSurvive()
{
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    return std::vector<std::size_t> {
        getDistanceUp(posX, posY),
        getDistanceDown(posX, posY),
        getDistanceLeft(posX, posY),
        getDistanceRight(posX, posY)
    };
}

ACharacter::Action  Bot::getOutOfDanger()
{
    std::cout << "GET OUT OF DANGER" << std::endl;
    if (_transformedMap[std::get<1>(_2dPos)][std::get<0>(_2dPos)] == '0')
        return ACharacter::Action::WAIT;
    std::size_t     index {0};
    auto            distances = getDistancesToSurvive();
    auto            minElement = std::max_element(distances.begin(), distances.end());
    for (auto tmp {distances.begin()}; tmp != minElement; ++tmp)
        index += 1;
    std::cout << "distances:" << std::endl;
    for (auto d : distances)
        std::cout << d << std::endl;
    std::cout << std::endl;
    if (distances[index] == 0) {
        auto posX = std::get<0>(_2dPos);
        auto posY = std::get<1>(_2dPos);
        if (posX < _transformedMap[posY].size() - 1 and _transformedMap[posY][posX + 1] == '3')
            return ACharacter::Action::RIGHT;
        else if (posY < _transformedMap.size() - 1 and _transformedMap[posY + 1][posX] == '3')
            return ACharacter::Action::DOWN;
        else if (posY > 0 and _transformedMap[posY - 1][posX] == '3')
            return ACharacter::Action::UP;
        else if (posX > 0 and _transformedMap[posY][posX - 1] == '3')
            return ACharacter::Action::LEFT;
        else
            return ACharacter::Action::WAIT;
    }
    return ACharacter::Action(index);
}

bool            Bot::isSafe(const float &x, const float &y)
{
    return y >= 0 and y < _transformedMap.size() - 1
        and x >= 0 and x < _transformedMap[y].size() - 1
        and _transformedMap[y][x] == '0';
}

ACharacter::Action  Bot::chooseDirection()
{
    std::vector<ACharacter::Action> directions;
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    if (isSafe(posX, posY - 1))
        directions.push_back(ACharacter::Action::UP);
    if (isSafe(posX, posY + 1))
        directions.push_back(ACharacter::Action::DOWN);
    if (isSafe(posX - 1, posY))
        directions.push_back(ACharacter::Action::LEFT);
    if (isSafe(posX + 1, posY))
        directions.push_back(ACharacter::Action::RIGHT);
    if (directions.empty())
        std::cout << "grosse pute" << std::endl;
    auto randDirection = std::rand() / (RAND_MAX + directions.size());
    return directions.empty() ? ACharacter::Action::WAIT : directions[randDirection];
}

void    Bot::changePosition(const ACharacter::Action &a) {
    if (a == ACharacter::Action::UP) {
//        std::get<2>(_pos) += 10;
        std::get<1>(_2dPos) -= 1;
        _movement = 10;
    } else if (a == ACharacter::Action::DOWN) {
//        std::get<2>(_pos) -= 10;
        std::get<1>(_2dPos) += 1;
        _movement = 10;
    } else if (a == ACharacter::Action::LEFT) {
//        std::get<0>(_pos) -= 10;
        std::get<0>(_2dPos) -= 1;
        _movement = 10;
    } else if (a == ACharacter::Action::RIGHT) {
//        std::get<0>(_pos) += 10;
        std::get<0>(_2dPos) += 1;
        _movement = 10;
    }
}

void    Bot::bombExplosion()
{
    for (auto j {0}; j < _transformedMap.size(); ++j) {
        for (auto i = 0; i < _transformedMap[j].size(); ++i) {
            if (_transformedMap[j][i] == '4') {
                _transformedMap[j][i] = '0';
                if (j > 0 and (_transformedMap[j - 1][i] == '3' or _transformedMap[j - 1][i] == '2'))
                    _transformedMap[j - 1][i] = '0';
                if (j < _transformedMap.size() - 1 and (_transformedMap[j + 1][i] == '3' or _transformedMap[j + 1][i] == '2'))
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
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    std::cout << "Pos X = " << posX << std::endl;
    std::cout << "Pos Y = " << posY << std::endl;

    _transformedMap[posY][posX] = '4';
    if (posY > 0 and _transformedMap[posY - 1][posX] != '1'
            and _transformedMap[posY - 1][posX] != '2')
        _transformedMap[posY - 1][posX] = '3';

    if (posY < _transformedMap.size() - 1 and _transformedMap[posY + 1][posX] != '1'
            and _transformedMap[posY + 1][posX] != '2')
        _transformedMap[posY + 1][posX] = '3';

    if (posX > 0 and _transformedMap[posY][posX - 1] != '1'
            and _transformedMap[posY][posX - 1] != '2')
        _transformedMap[posY][posX - 1] = '3';

    if (posX < _transformedMap[posY].size() - 1 and _transformedMap[posY][posX + 1] != '1'
            and _transformedMap[posY][posX + 1] != '2')
        _transformedMap[posY][posX + 1] = '3';
}

void    Bot::animation()
{
    switch (_lastDirection) {
        case ACharacter::Action::UP:
            std::get<2>(_pos) += 1;
            break;
        case ACharacter::Action::DOWN:
            std::get<2>(_pos) -= 1;
            break;
        case ACharacter::Action::LEFT:
            std::get<0>(_pos) -= 1;
            break;
        case ACharacter::Action::RIGHT:
            std::get<0>(_pos) += 1;
            break;
        default:
            break;
    }
    _movement -= 1;
}

void    Bot::move(std::vector<std::string> &map, IDisplay *d)
{
    static auto c = std::chrono::system_clock::now();
    static auto count {0};

    if (_movement > 0) {
        animation();
        return;
    }
    _transformedMap = map;
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - c;
    if (diff.count() > 0.3)
        c = std::chrono::system_clock::now();
    else
        return;
    for (auto t : _transformedMap)
        std::cout << t << std::endl;
    std::cout << std::endl;
    Action  a;
    if (_bombNumber == 0 && count >= 5) {
        count = 0;
        std::cout << "BOMB EXPLOSION" << std::endl;
        _bombNumber += 1;
        bombExplosion();
        a = ACharacter::Action::WAIT;
    } else if (_bombNumber == 0) {
        a = getOutOfDanger();
        changePosition(a);
    } else if (isMomentForBomb()) {
        std::cout << "BOMB" << std::endl;
        a = ACharacter::Action::BOMB;
        putBomb();
        decreaseBombNumber();
    } else {
        a = chooseDirection();
        changePosition(a);
    }
    map = _transformedMap;
    _lastDirection = a;
    ++count;
}