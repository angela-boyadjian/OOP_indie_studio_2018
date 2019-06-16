/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** LoadManager
*/

#include <iostream>

#include <Bomberman/BombermanGame.hpp>
#include "LoadManager.hpp"

LoadManager::LoadManager() : _index(0), _isMapWall(false),
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

MapData &LoadManager::getMapData()
{
    if (!_isGameLoaded)
        std::cerr << "Careful ! Game not loaded. Problems incoming !" << std::endl;
    return _mapData;
}

void LoadManager::getMapWall(std::string const &line)
{
    _mapData._mapWall.push_back(line);
}

void LoadManager::getRulesWall(std::string const &line)
{
    _mapData._rulesWall.insert({line[_index], getSpriteInfo(line)});
    _index = 0;
}

void LoadManager::getRulesGround(std::string const &line)
{
    _mapData._rulesGround.insert({line[_index], getSpriteInfo(line)});
    _index = 0;
}

std::string const LoadManager::getPath(std::string const &line)
{
    std::string path;

    while (line[_index++] != ':')
        path.push_back(line[_index]);
    ++_index;
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
    _index = 4;
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
            _mapData._time = line[2] - 48;
            break;
        case 'E' :
            _mapData._nbEnnemie = line[2] - 48;
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
        if (!_isMapWall && !_isRulesWall && !_isRulesGround) {
            if (line.compare("MapWall") == 0)
                _isMapWall = true;
            else if (line.compare("RulesWall")) {
                _isRulesWall = true;
                _isMapWall = false;
            } else if (line.compare("RulesGround")) {
                _isRulesGround = true;
                _isRulesWall = false;
            }
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
        getSkin(line), pos)));
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
        << std::get<1>(pos) << " " << std::get<2>(pos) << std::endl;
}