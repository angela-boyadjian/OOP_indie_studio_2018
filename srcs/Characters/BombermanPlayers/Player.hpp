/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#pragma once

#include "ABombermanPlayer.hpp"

class Player : public ABombermanPlayer {
public:
    // NOTE ADD KEYMAP PARAM TO CHANGE THE PLAYER KEYMAP
    Player(const std::size_t &, ACharacter::Color, MapPos const &pos);
    ~Player();

    void    move(const std::vector<std::string> &, IDisplay *) final;
};