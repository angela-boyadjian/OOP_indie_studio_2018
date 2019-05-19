/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#pragma once

#include "ACharacter.hpp"

class Player : public ACharacter {
public:
    // ADD KEYMAP PARAM TO CHANGE THE PLAYER KEYMAP
    Player(const std::size_t &, ACharacter::Color, MapPos const &pos);
    ~Player();
    void    up(IDisplay *);
    void    down(IDisplay *);
    void    left(IDisplay *);
    void    right(IDisplay *);
    void    move(const std::vector<std::string> &, IDisplay *) final;

private:
};