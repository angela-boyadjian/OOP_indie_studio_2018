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

class SaveManager : public ISave {
public:
    SaveManager(AGame &);
    ~SaveManager();

public:
    void save();

private:
    void createFile();
    void addCharacters();
    std::string const getPos(ACharacter const &);
    std::string const getColor(ACharacter const &);

private:
    std::ofstream       _file;
    std::vector<Bot>    _bots;
    std::vector<Player> _players;
};