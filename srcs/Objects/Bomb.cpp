/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb() : _isPlaced(false)
{
}

Bomb::~Bomb()
{
}

void Bomb::place()
{
    _isPlaced = true;
}

void Bomb::explode()
{
    
}

std::string const Bomb::getRes() const
{
    return "../resources/models/Bomb/Bomb.obj";
}

std::string const Bomb::getTexture() const
{
    return "../resources/models/Bomb/Bomb.png";
}