/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SaveManager
*/

#include "SaveManager.hpp"
#include <iostream>

SaveManager::SaveManager(AGame &g, MapData &mapData) : _mapData(mapData)
{
    for (auto &p : g.getPlayers())
        _players.push_back(*p.get());
    for (auto &b : g.getBots())
        _bots.push_back(*b.get());
}

SaveManager::~SaveManager()
{
    if (_file.is_open())
        _file.close();
}

void SaveManager::save()
{
    createFile();
    addCharacters();
    addMap();
}

void SaveManager::createFile()
{
    _file.open("../srcs/Game/Save/save.txt", std::ios::in | std::ios::trunc);
    if (!_file)
        std::cerr << "Failed to open save.txt" << std::endl;
}

std::string const SaveManager::getPos(ACharacter const &c)
{
    auto pos {c.getMapPos()};
    auto line = std::to_string(std::get<0>(pos)) + " " +
        std::to_string(std::get<1>(pos)) +  " " +
            std::to_string(std::get<2>(pos)) + ":";
    std::cout << "IN SAVE :\n";
    std::cout << "Pos = " << std::get<0>(pos) << " "
        << std::get<1>(pos) << " " << std::get<2>(pos) << "\n";
    std::cout << "Result = " << line << std::endl;
    return line;
}

std::string const SaveManager::getColor(ACharacter const &c)
{
    return std::to_string(static_cast<int>(c._color)) + ":";
}

void SaveManager::addMap()
{
    addMapWall();
    addRules();
    _file << "T:" << std::to_string(_mapData._time) << std::endl;
    _file << "E:" << std::to_string(_mapData._nbEnnemie) << std::endl;
}

void SaveManager::addMapWall() noexcept
{
    _file << "MapWall" << std::endl;

    for (auto const &wall : _mapData._mapWall)
        _file << wall << std::endl;
}

void SaveManager::addRules()
{
    _file << "RulesWall" << std::endl;
    for (auto const &wall : _mapData._rulesWall) {
        _file << wall.first << ":";
        addSpriteInfo(wall.second);
        _file << std::endl;
    }
    _file << "RulesGround" << std::endl;
    for (auto const &ground : _mapData._rulesGround) {
        _file << ground.first << ":";
        addSpriteInfo(ground.second);
        _file << std::endl;
    }
}

void SaveManager::addSpriteInfo(SpriteInfo const &info)
{
    _file << info._referTo << ":" << info._messPath << ":" << info._texPath << ":";
    _file << std::to_string(info._size.X) << " " <<
        std::to_string(info._size.Y) << " " << std::to_string(info._size.Z) << ":";
    _file << std::to_string(info._is_destructible);
}

void SaveManager::addCharacters()
{
    for (auto const &p : _players)
        _file << "P:" << getPos(p) << getColor(p) << std::to_string(p.getBombNb()) << std::endl;
    for (auto const &b : _bots)
        _file << "B:" << getPos(b) << getColor(b) << std::to_string(b.getBombNb()) << std::endl;
}