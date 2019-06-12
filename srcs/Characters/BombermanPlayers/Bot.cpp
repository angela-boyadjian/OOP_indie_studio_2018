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

bool            Bot::isBlock(const float &x, const float &y, std::vector<std::string> &map)
{
    return y >= 0 and y < map.size()
            and x >= 0 and x < map[y].size()
            and (map[y][x] == '1'
            or map[y][x] == '2');
}

std::size_t     Bot::countBlock(std::vector<std::string> &map)
{
    std::size_t count {0};
    auto        posX {std::get<0>(_2dPos)};
    auto        posY {std::get<1>(_2dPos)};

    if (isBlock(posX, posY + 1, map))
        ++count;
    if (isBlock(posX, posY - 1, map))
        ++count;
    if (isBlock(posX + 1, posY, map))
        ++count;
    if (isBlock(posX - 1, posY, map))
        ++count;
    return count;
}

bool            Bot::isMomentForBomb(std::vector<std::string> &map)
{
    return _bombNumber > 0 and countBlock(map) >= 2;
}

bool            Bot::isInDanger(std::vector<std::string> &map)
{
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};
    return map[posY][posX] == -1 or map[posY][posX] == -2;
}

std::size_t Bot::getDistanceUp(float x, float y, std::vector<std::string> &map)
{
    std::size_t count {0};
    while (--y >= 0) {
        if (map[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::size_t Bot::getDistanceDown(float x, float y, std::vector<std::string> &map)
{
    std::size_t count {0};
    while (++y < map.size()) {
        if (map[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::size_t Bot::getDistanceLeft(float x, float y, std::vector<std::string> &map)
{
    std::size_t count {0};
    while (--x >= 0) {
        if (map[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::size_t Bot::getDistanceRight(float x, float y, std::vector<std::string> &map)
{
    std::size_t count {0};
    while (++x < map[y].size()) {
        if (map[y][x] != '0')
            return count;
        count += 1;
    }
    return count;
}

std::vector<std::size_t> Bot::getDistancesToSurvive(std::vector<std::string> &map)
{
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    return std::vector<std::size_t> {
        getDistanceUp(posX, posY, map),
        getDistanceDown(posX, posY, map),
        getDistanceLeft(posX, posY, map),
        getDistanceRight(posX, posY, map)
    };
}

ACharacter::Action  Bot::getOutOfDanger(std::vector<std::string> &map)
{
    std::cout << "GET OUT OF DANGER" << std::endl;
    if (map[std::get<1>(_2dPos)][std::get<0>(_2dPos)] == '0')
        return ACharacter::Action::WAIT;
    std::size_t     index {0};
    auto            distances = getDistancesToSurvive(map);
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
        if (posX < map[posY].size() - 1 and map[posY][posX + 1] == '3')
            return ACharacter::Action::RIGHT;
        else if (posY < map.size() - 1 and map[posY + 1][posX] == '3')
            return ACharacter::Action::DOWN;
        else if (posY > 0 and map[posY - 1][posX] == '3')
            return ACharacter::Action::UP;
        else if (posX > 0 and map[posY][posX - 1] == '3')
            return ACharacter::Action::LEFT;
        else
            return ACharacter::Action::WAIT;
    }
    return ACharacter::Action(index);
}

bool            Bot::isSafe(const float &x, const float &y, std::vector<std::string> &map)
{
    return y >= 0 and y < map.size() - 1
        and x >= 0 and x < map[y].size() - 1
        and map[y][x] == '0';
}

ACharacter::Action  Bot::chooseDirection(std::vector<std::string> &map)
{
    std::vector<ACharacter::Action> directions;
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    if (isSafe(posX, posY - 1, map))
        directions.push_back(ACharacter::Action::UP);
    if (isSafe(posX, posY + 1, map))
        directions.push_back(ACharacter::Action::DOWN);
    if (isSafe(posX - 1, posY, map))
        directions.push_back(ACharacter::Action::LEFT);
    if (isSafe(posX + 1, posY, map))
        directions.push_back(ACharacter::Action::RIGHT);
    if (directions.empty())
        std::cout << "grosse pute" << std::endl;
    auto randDirection = std::rand() / (RAND_MAX + directions.size());
    return directions.empty() ? ACharacter::Action::WAIT : directions[randDirection];
}

void    Bot::changePosition(const ACharacter::Action &a) {
    if (a == ACharacter::Action::UP) {
        std::get<1>(_2dPos) -= 1;
        _movement = 10;
    } else if (a == ACharacter::Action::DOWN) {
        std::get<1>(_2dPos) += 1;
        _movement = 10;
    } else if (a == ACharacter::Action::LEFT) {
        std::get<0>(_2dPos) -= 1;
        _movement = 10;
    } else if (a == ACharacter::Action::RIGHT) {
        std::get<0>(_2dPos) += 1;
        _movement = 10;
    }
}

void    Bot::bombExplosion(std::vector<std::string> &map)
{
    for (auto j {0}; j < map.size(); ++j) {
        for (auto i = 0; i < map[j].size(); ++i) {
            if (map[j][i] == '5') {
                map[j][i] = '0';
                for (auto k {1}; k < _fireRange + 1; ++k) {
                    if (j - (k - 1) > 0 and (map[j - k][i] == '3' or map[j - k][i] == '2'))
                        map[j - k][i] = '0';
                    if (j + (k - 1) < map.size() and (map[j + k][i] == '3' or map[j + k][i] == '2'))
                        map[j + k][i] = '0';
                    if (i - (k - 1) > 0 and (map[j][i - k] == '3' or map[j][i - k] == '2'))
                        map[j][i - k] = '0';
                    if (i + (k - 1) < map[j].size() and (map[j][i + k] == '3' or map[j][i + k] == '2'))
                        map[j][i + k] = '0';
                }
            }
        }
    }
}

void    Bot::putBomb(std::vector<std::string> &map)
{
    auto    posX {std::get<0>(_2dPos)};
    auto    posY {std::get<1>(_2dPos)};

    std::cout << "Pos X = " << posX << std::endl;
    std::cout << "Pos Y = " << posY << std::endl;

    map[posY][posX] = '5';
    for (auto i {1}; i < _fireRange + 1; ++i) {
        if (posY - (i - 1) > 0 and map[posY - i][posX] != '1'
                and map[posY - i][posX] != '2')
            map[posY - i][posX] = '3';

        if (posY + (i - 1) < map.size() and map[posY + i][posX] != '1'
                and map[posY + i][posX] != '2')
            map[posY + i][posX] = '3';

        if (posX - (i - 1) > 0 and map[posY][posX - i] != '1'
                and map[posY][posX - i] != '2')
            map[posY][posX - i] = '3';

        if (posX + (i - 1) < map[posY].size() and map[posY][posX + i] != '1'
                and map[posY][posX + i] != '2')
            map[posY][posX + i] = '3';
    }
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
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - c;
    if (diff.count() > 0.3)
        c = std::chrono::system_clock::now();
    else
        return;
    for (auto &t : map)
        std::cout << t << std::endl;
    std::cout << std::endl;
    Action  a;
    if (_bombNumber == 0 && count >= 5) {
        count = 0;
        std::cout << "BOMB EXPLOSION" << std::endl;
        _bombNumber += 1;
        bombExplosion(map);
        a = ACharacter::Action::WAIT;
    } else if (_bombNumber == 0) {
        a = getOutOfDanger(map);
        changePosition(a);
    } else if (isMomentForBomb(map)) {
        std::cout << "BOMB" << std::endl;
        a = ACharacter::Action::BOMB;
        putBomb(map);
        decreaseBombNumber();
    } else {
        a = chooseDirection(map);
        changePosition(a);
    }
    _lastDirection = a;
    ++count;
}