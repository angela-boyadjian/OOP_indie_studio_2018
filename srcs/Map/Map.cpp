/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/
#include <irrlicht.h>
// #include <zconf.h>

#include "Map.hpp"
#include "IrrlichtDisplay/IrrlichtDisplay.hpp"
#include "Reader.hpp"

Map::Map(std::string const &filename) : _filename(filename)
{
}

Map::~Map()
{
}

// NOTE Load les data qui serviront a load les objets 3D

void Map::load()
{
    Reader reader;
    std::vector<std::string> vec;

    _data._mapWall = reader.vectorRead(_filename);
    auto infosWall = reader.readSpriteInfo(_data._mapWall.back());
    auto infosGround = reader.readSpriteInfo(
        _data._mapWall[_data._mapWall.size() - 2]);
    _data._rulesWall = loadRules(infosWall);
    _data._rulesGround = loadRules(infosGround);
    _data._nbEnnemie = static_cast<unsigned int>(std::stoi(_data._mapWall[0]));
    _data._time = static_cast<unsigned int>(std::stoi(_data._mapWall[1]));
    _data._mapWall.erase(_data._mapWall.end() - 2, _data._mapWall.end());
    _data._mapWall.erase(_data._mapWall.begin(), _data._mapWall.begin() + 2);
    // GESTION D'ERREUR A AJOUTER;
}

std::unordered_map<char, SpriteInfo> Map::loadRules(std::vector<SpriteInfo> &infos)
{
    std::unordered_map<char, SpriteInfo> map;

    for (auto &info : infos)
        map.insert({info._referTo[0], info});
    return map;
}

MapData Map::getMapData() const
{
    return _data;
}
