/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ISave
*/

#pragma once

#include <string>

#include "SpriteInfo.hpp"
#include "ACharacter.hpp"

class ISave {
public:
    ISave() = default;
    virtual ~ISave() {}
    virtual void save() = 0;

private:
    virtual void addMap() = 0;
    virtual void addRules() = 0;
    virtual void createFile() = 0;
    virtual void addCharacters() = 0;
    virtual void addMapWall() noexcept = 0;
    virtual void addSpriteInfo(SpriteInfo const &) = 0;
    virtual std::string const getPos(ACharacter const &) = 0;
    virtual std::string const getColor(ACharacter const &) = 0;
};