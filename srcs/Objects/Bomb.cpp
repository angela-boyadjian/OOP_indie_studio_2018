/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb() : _isPlaced(false), _on(false)
{
}

Bomb::~Bomb() {}

void Bomb::place()
{
    _isPlaced = true;
}

void Bomb::explode()
{
    _isPlaced = false;
}

bool Bomb::isPlaced() const
{
    return _isPlaced;
}

bool Bomb::isOn() const
{
    return _on;
}

void Bomb::setOn(bool value)
{
    _on = value;
}

std::string const Bomb::getRes() const
{
    return "../resources/models/Bomb/Bomb.obj";
}

std::string const Bomb::getTexture() const
{
    return "../resources/models/Bomb/Bomb.png";
}