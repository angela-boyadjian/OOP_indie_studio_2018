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
    Player(ACharacter::Color, MapPos const &pos, Display &display);
    ~Player();

    void loadPlayer();

    void displayPlayer();

    void move(const std::vector<std::string> &);
private:
    Display _display;
    Color _color;
};