/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#pragma once

#include "Display.hpp"
#include "ACharacter.hpp"

class Player : public ACharacter {
public:
    Player(MapPos const &pos, Display &display);
    ~Player();

    void loadPlayer();

    void displayPlayer();

    void move();
private:
    Display _display;
};