/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** LoadManager
*/

#pragma once

#include <fstream>

#include "ILoad.hpp"
#include "Player.hpp"
#include "Bot.hpp"

class LoadManager : public ILoad {
public:
    using PlayerVec = std::vector<std::unique_ptr<Player>>;
    using BotVec = std::vector<std::unique_ptr<Bot>>;

    LoadManager();
    ~LoadManager();

    std::unique_ptr<AGame> load();

private:
    void addCharacter(std::string const &);
    ACharacter::MapPos  getMapPos(std::string const &, int);
    void printPos(ACharacter::MapPos const &) const;
    float convertVal(std::string &, int &);
private:
    BotVec          _bots;
    std::ifstream   _file;
    PlayerVec       _players;
    std::size_t     _index;
};