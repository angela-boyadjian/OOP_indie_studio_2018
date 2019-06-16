/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ILoad
*/

#pragma once

#include "AGame.hpp"

class ILoad {
public:
    ILoad() = default;
    virtual ~ILoad() {};

public:
    virtual MapData &getMapData() = 0;
    virtual std::unique_ptr<AGame> loadGame() = 0;

private:
    virtual void                    addBot(std::string const &) = 0;
    virtual void                    getInfo(std::string const &) = 0;
    virtual irr::core::vector3df    getSize(std::string const &) = 0;
    virtual std::string const       getPath(std::string const &) = 0;
    virtual ACharacter::Color       getSkin(std::string const &) = 0;
    virtual void                    addPlayer(std::string const &) = 0;
    virtual void                    getMapWall(std::string const &) = 0;
    virtual float                   convertVal(std::string &, int &) = 0;
    virtual void                    getRulesWall(std::string const &) = 0;
    virtual void                    getRulesGround(std::string const &) = 0;
    virtual SpriteInfo              &getSpriteInfo(std::string const &) = 0;
    virtual ACharacter::MapPos      getMapPos(std::string const &, int) = 0;
    virtual void                    printPos(ACharacter::MapPos const &) const = 0;
};