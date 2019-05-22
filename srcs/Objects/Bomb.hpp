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
    // Bomb(Bomb const &) = delete;
    // Bomb &operator=(Bomb const &) = delete;
    ~Bomb();

    // NOTE Action
    void explode();
    void place();
    bool isPlaced() const;
    bool isOn() const;

    // NOTE Setter
    void setOn(bool);

    // NOTE Getters
    std::string const getRes() const;
    std::string const getTexture() const;
private:
    bool        _isPlaced;
    bool        _on;
};