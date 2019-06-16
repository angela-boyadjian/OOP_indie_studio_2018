/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** LoadManager
*/

#include <iostream>

#include <Bomberman/BombermanGame.hpp>
#include "LoadManager.hpp"
#include <Map.hpp>

LoadManager::LoadManager() : _map(new Map()), _index(0), _isMapWall(false),
    _isRulesWall(false), _isGameLoaded(false), _isRulesGround(false)
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

std::shared_ptr<IMap> LoadManager::getMap()
{
    for (std::string line; std::getline(_file, line);) {
        if (line.compare("MapWall") == 0) {
            _isMapWall = true;
        } else if (line.compare("RulesWall") == 0) {
            _isRulesWall = true;
            _isMapWall = false;
        } else if (line.compare("RulesGround") == 0) {
            _isRulesGround = true;
            _isRulesWall = false;
        } else {
            getInfo(line);
        }
    }
    return _map;
}

void LoadManager::getMapWall(std::string const &line)
{
    _map->getMapData()._mapWall.push_back(line);
}

void LoadManager::getRulesWall(std::string const &line)
{
    _map->getMapData()._rulesWall.insert({line[0], getSpriteInfo(line)});
    _index = 0;
}

void LoadManager::getRulesGround(std::string const &line)
{
    _map->getMapData()._rulesGround.insert({line[0], getSpriteInfo(line)});
    _index = 0;
}

std::string const LoadManager::getPath(std::string const &line)
{
    std::string path;

    ++_index;
    while (line[_index] != ':') {
        path.push_back(line[_index]);
        ++_index;
    }
    return path;
}

irr::core::vector3df LoadManager::getSize(std::string const &line)
{
    std::string tmp;
    irr::core::vector3df vec;
    auto count {0};

    while (line[_index++]) {
        if (line[_index] == ' ' && count == 0) {
            vec.X = convertVal(tmp, count);
        } else if (line[_index] == ' ' && count == 1) {
            vec.Y = convertVal(tmp, count);
        } else if (line[_index] == ':') {
            vec.Z = std::atof(tmp.c_str());
            break;
        }
        tmp.push_back(line[_index]);
    }
    ++_index;
    return vec;
}

SpriteInfo &LoadManager::getSpriteInfo(std::string const &line)
{
    _index = 3;
    auto sprite = new SpriteInfo(SpriteInfo(std::to_string(line[0]), getPath(line),
        getPath(line), getSize(line), line[_index] == '1' ? true : false));

    return *sprite;
}

void LoadManager::getInfo(std::string const &line)
{
    switch (line[0]) {
        case 'P' :
            addPlayer(line);
            break;
        case 'B' :
            addBot(line);
            break;
        case 'T' :
            _map->getMapData()._time = line[2] - 48;
            break;
        case 'E' :
            _map->getMapData()._nbEnnemie = line[2] - 48;
            break;
        default :
            if (_isMapWall)
                getMapWall(line);
            else if (_isRulesWall)
                getRulesWall(line);
            else if (_isRulesGround)
                getRulesGround(line);
            break;
    }
}

std::unique_ptr<AGame> LoadManager::loadGame()
{
    std::string line;

    while (std::getline(_file, line)) {
        if (line.compare("MapWall") == 0) {
            _isMapWall = true;
        } else if (line.compare("RulesWall") == 0) {
            _isRulesWall = true;
            _isMapWall = false;
        } else if (line.compare("RulesGround") == 0) {
            _isRulesGround = true;
            _isRulesWall = false;
        } else {
            getInfo(line);
        }
    }
    _isGameLoaded = true;
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

    --i;
    while (line[i++]) {
        if (line[i] == ' ' && count == 0) {
            x = convertVal(tmp, count);
        } else if (line[i] == ' ' && count == 1) {
            y = convertVal(tmp, count);
        } else if (line[i] == ':') {
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
    auto n {line[_index] - 48};

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
        ACharacter::Color::RED, pos)));
    _index = 0;
}

void LoadManager::addBot(std::string const &line)
{
    auto pos {getMapPos(line, 2)};

    _bots.push_back(std::make_unique<Bot>(Bot(1, ACharacter::Color::RED, pos)));
}

void LoadManager::printPos(ACharacter::MapPos const &pos) const
{
    std::cout << "Pos = " << std::get<0>(pos) << " "
        << std::get<1>(pos) << " " << std::get<2>(pos) << ":";
}

void LoadManager::printCharacter() const
{
    std::cout << "Players" << std::endl;
    if (_players.empty())
        std::cout << "player empty" << std::endl;
    if (_bots.empty())
        std::cout << "bots empty" << std::endl;
    for (auto & i : _players) {
        printPos(i->getMapPos());
        std::cout << std::endl;
    }
    std::cout << "Bots" << std::endl;
    for (auto & i : _bots) {
        printPos(i->getMapPos());
        std::cout << std::endl;
    }
}

void LoadManager::printMap() const
{
    auto map = _map->getMapData();

    std::cout << "Map walls:" << std::endl;
    for (auto &i : map._mapWall)
        std::cout << i << std::endl;
    std::cout << "Rules wall first:" << std::endl;
    for (auto &i : map._rulesWall) {
        std::cout << i.first << ":" << i.second._messPath << ":" << i.second._texPath << ":";
        auto pos = i.second._size;
        std::cout << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
    }
    std::cout << "Rules Ground first:" << std::endl;
    for (auto &i : map._rulesGround) {
        std::cout << i.first << ":" << i.second._messPath << ":" << i.second._texPath << ":";
        auto pos = i.second._size;
        std::cout << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
    }
}