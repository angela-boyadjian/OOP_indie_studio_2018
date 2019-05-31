/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#pragma once

#include <string>

class Bomb {
public:
    Bomb();
    ~Bomb();

    // NOTE Action
    void explode();
    void place();

    // NOTE Getter
    std::string const getRes() const;
    std::string const getTexture() const;
private:
    bool        _isPlaced;
};
