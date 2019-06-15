/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** LoadManager
*/

#include <iostream>

#include <Bomberman/BombermanGame.hpp>
#include "LoadManager.hpp"

LoadManager::LoadManager() : _index(0)
{
    _file.open("../srcs/Game/Save/save.txt");

    if (!_file)
        std::cerr << "Unable to open file save.txt";
}

LoadManager::~LoadManager()
{
    if (_file.is_open())
        _file.close();
}

std::unique_ptr<AGame> LoadManager::load()
{
    std::string line;

    while (std::getline(_file, line)) {
        switch (line[0]) {
            case 'P' :
                addPlayer(line);
                break;
            case 'B' :
                addBot(line);
                break;
            default :
                break;
        }
    }
    return std::unique_ptr<AGame>(new BombermanGame(_players, _bots));
}

float LoadManager::convertVal(std::string &tmp, int &count)
{
    auto num {std::atof(tmp.c_str())};

    tmp.clear();
    ++count;
    return num;
}

// NOTE std::get<val>(pos) -> Val need to be const
ACharacter::MapPos LoadManager::getMapPos(std::string const &line, int i)
{
    std::string tmp;
    float x = 0, y = 0, z = 0;
    auto count {0};

    while (line[i++]) {
        if (line[i] == ' ' && count == 0) {
            x = convertVal(tmp, count);
        } else if (line[i] == ' ' && count == 1) {
            y = convertVal(tmp, count);
        } else if (line[i] == '/') {
            z = std::atof(tmp.c_str());
            _index = i + 1;
            break;
        }
        tmp.push_back(line[i]);
    }
    return std::make_tuple(x, y, z);
}

ACharacter::Color LoadManager::getSkin(std::string const &line)
{
    auto n {line[_index] + 48};

    _index += 2;
    switch (n) {
        case 0 :
            return ACharacter::Color::BLACK;
        case 1 :
            return ACharacter::Color::PINK;
        case 2 :
            return ACharacter::Color::RED;
        default :
            return ACharacter::Color::WHITE;
    }
}

void LoadManager::addPlayer(std::string const &line)
{
    auto pos {getMapPos(line, 2)};

    _players.push_back(std::make_unique<Player>(Player(0,
        ACharacter::Color::PINK, pos)));
}


void LoadManager::addBot(std::string const &line)
{
    auto pos {getMapPos(line, 2)};

    _bots.push_back(std::make_unique<Bot>(Bot(1, pos)));
}

void LoadManager::printPos(ACharacter::MapPos const &pos) const
{
    std::cout << "Pos = " << std::get<0>(pos) << " "
        << std::get<1>(pos) << " " << std::get<2>(pos) << std::endl;
}