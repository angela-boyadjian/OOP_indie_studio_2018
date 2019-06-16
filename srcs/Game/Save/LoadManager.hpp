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
#include "MapData.hpp"
#include "SpriteInfo.hpp"

class LoadManager : public ILoad {
public:
    using PlayerVec = std::vector<std::shared_ptr<Player>>;
    using BotVec = std::vector<std::shared_ptr<Bot>>;

    LoadManager();
    ~LoadManager();

    std::shared_ptr<IMap> getMap();
    std::unique_ptr<AGame> loadGame();

private:
    // NOTE Add
    void addBot(std::string const &);
    void addPlayer(std::string const &);

    // NOTE Utils
    ACharacter::Color       getSkin(std::string const &);
    void                    getInfo(std::string const &);
    irr::core::vector3df    getSize(std::string const &);
    void                    getMapWall(std::string const &);
    std::string const       getPath(std::string const &);
    float                   convertVal(std::string &, int &);
    void                    getRulesWall(std::string const &);
    void                    getRulesGround(std::string const &);
    SpriteInfo              &getSpriteInfo(std::string const &);
    ACharacter::MapPos      getMapPos(std::string const &, int);

    // NOTE Display
    void printPos(ACharacter::MapPos const &) const;
    void printMap() const;
private:
    std::shared_ptr<IMap>   _map;
    BotVec                  _bots;
    std::ifstream           _file;
    std::size_t             _index;
    PlayerVec               _players;
    bool                    _isMapWall;
    bool                    _isRulesWall;
    bool                    _isGameLoaded;
    bool                    _isRulesGround;
};