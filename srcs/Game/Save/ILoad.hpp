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
    virtual std::unique_ptr<AGame> load() = 0;
private:
};