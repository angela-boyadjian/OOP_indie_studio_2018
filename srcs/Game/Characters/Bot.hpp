/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bot
*/

#pragma once

#include "ACharacter.hpp"

class Bot : public ACharacter {
public:
    Bot(const MapPos &pos) : ACharacter(pos) {};
    ~Bot() = default;
};