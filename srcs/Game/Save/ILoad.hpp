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
    virtual void addBot(std::string const &) = 0;
    virtual void addPlayer(std::string const &) = 0;
    virtual float convertVal(std::string &, int &) = 0;
    virtual ACharacter::Color getSkin(std::string const &) = 0;
    virtual void printPos(ACharacter::MapPos const &) const = 0;
    virtual ACharacter::MapPos  getMapPos(std::string const &, int) = 0;
};