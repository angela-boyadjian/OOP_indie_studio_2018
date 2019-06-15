/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SaveManager
*/

#pragma once

#include <fstream>

#include "AGame.hpp"
#include "ISave.hpp"
#include "IMap.hpp"

class SaveManager : public ISave {
public:
    SaveManager(AGame &, MapData &);
    ~SaveManager();

public:
    void save();

private:
    void addMap();
    void addRules();
    void createFile();
    void addCharacters();
    void addMapWall() noexcept;
    void addSpriteInfo(SpriteInfo const &);
    std::string const getPos(ACharacter const &);
    std::string const getColor(ACharacter const &);

private:
    MapData             &_mapData;
    std::ofstream       _file;
    std::vector<Bot>    _bots;
    std::vector<Player> _players;
};