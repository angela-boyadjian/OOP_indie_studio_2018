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
    using PlayerVec = std::vector<std::shared_ptr<Player>>;
    using BotVec = std::vector<std::shared_ptr<Bot>>;

    LoadManager();
    ~LoadManager();

    std::unique_ptr<AGame> load();

private:
    // NOTE Add
    void addBot(std::string const &);
    void addPlayer(std::string const &);

    // NOTE Utils
    float convertVal(std::string &, int &);
    ACharacter::Color getSkin(std::string const &);
    ACharacter::MapPos  getMapPos(std::string const &, int);

    // NOTE Display
    void printPos(ACharacter::MapPos const &) const;
private:
    BotVec          _bots;
    std::ifstream   _file;
    PlayerVec       _players;
    std::size_t     _index;
};