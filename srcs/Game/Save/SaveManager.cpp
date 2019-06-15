/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SaveManager
*/

#include "SaveManager.hpp"
#include <iostream>

SaveManager::SaveManager(AGame &g)
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
}

void SaveManager::createFile()
{
    // std::ofstream file("../srcs/Game/Save/save.txt", );
    // file.close();
    _file.open("../srcs/Game/Save/save.txt", std::ios::in | std::ios::trunc);
    if (!_file)
        std::cerr << "Failed to open save.txt" << std::endl;
}

std::string const SaveManager::getPos(ACharacter const &c)
{
    auto pos {c.getMapPos()};
    auto line = std::to_string(std::get<0>(pos)) + " " +
        std::to_string(std::get<1>(pos)) +  " " +
            std::to_string(std::get<2>(pos)) + "/";

    return line;
}

std::string const SaveManager::getColor(ACharacter const &c)
{
    return std::to_string(static_cast<int>(c._color)) + "/";
}

void SaveManager::addCharacters()
{
    for (auto const &p : _players) {
        _file << "P/" << getPos(p) << getColor(p) << std::to_string(p.getBombNb()) + "/";
        _file << std::endl;
    }
    for (auto const &b : _bots) {
        _file << "B/" << getPos(b) << getColor(b) << std::to_string(b.getBombNb()) + "/";
        _file << std::endl;
    }
}