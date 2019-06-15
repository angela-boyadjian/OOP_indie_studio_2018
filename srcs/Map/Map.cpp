/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/

// #include <zconf.h>

#include <irrlicht.h>
#include <cstdlib>
#include <ctime>

#include "Map.hpp"
#include "IrrlichtDisplay/IrrlichtDisplay.hpp"

Map::Map()
{
}

Map::~Map()
{
}

// NOTE Load les data qui serviront a load les objets 3D

void Map::load(const std::string &filename)
{
    std::vector<std::string> vec;

    _filename = filename;
    _data._mapWall = _reader.vectorRead(filename);
    auto infosWall = _reader.readSpriteInfo(_data._mapWall.back());
    auto infosGround = _reader.readSpriteInfo(
        _data._mapWall[_data._mapWall.size() - 2]);
    _data._rulesWall = loadRules(infosWall);
    _data._rulesGround = loadRules(infosGround);
    _data._nbEnnemie = static_cast<unsigned int>(std::stoi(_data._mapWall[0]));
    _data._time = static_cast<unsigned int>(std::stoi(_data._mapWall[1]));
    _data._mapWall.erase(_data._mapWall.end() - 2, _data._mapWall.end());
    _data._mapWall.erase(_data._mapWall.begin(), _data._mapWall.begin() + 2);
    // GESTION D'ERREUR A AJOUTER;
}

Map::Map_Template
Map::loadDefaultTemplate(const std::vector<std::string> &default_template)
{
    Map::Map_Template map_default;

    for (auto &file : default_template)
        map_default.emplace_back(_reader.vectorRead(file));
    return map_default;
}

std::vector<std::string> Map::DigStart(std::vector<std::string> &map)
{
    for (auto &line : map) {
        for (auto &tile : line)
            if (tile == '.')
                tile = '0';
    }
    return map;
}

void Map::generate3dMap(int template_index, int range, long seed)
{
    // std::cout << "coucou" << std::endl;
    auto files_names = _reader.readDir("./../resources/maps/map_template/");
    // std::cout << "coucou" << std::endl;
    auto default_template = loadDefaultTemplate(files_names);
    // std::cout << "coucou" << std::endl;

    if (seed == -1)
        std::srand(time(NULL));
    else
        std::srand(seed);
    if (template_index == -1)
        template_index = std::rand() % default_template.size();
    load(files_names[template_index]);
    for (auto &line : _data._mapWall) {
        for (auto &tile : line) {
            if (tile == '0') {
                auto rand_nb = (std::rand() % 100) + 1;
                if (rand_nb <= range)
                    tile = '2';
            }
        }
    }
}

std::unordered_map<char, SpriteInfo>
Map::loadRules(std::vector<SpriteInfo> &infos)
{
    std::unordered_map<char, SpriteInfo> map;

    for (auto &info : infos)
        map.insert({info._referTo[0], info});
    return map;
}

MapData &Map::getMapData()
{
    return _data;
}
