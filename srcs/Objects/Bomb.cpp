/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/
#include <memory>
#include <iostream>

#include "Bomb.hpp"

Bomb::Bomb() : _isPlaced(false), _on(false)
{
}

Bomb::~Bomb() {}

void Bomb::addMesh(Mesh *mesh)
{
    if (mesh) {
        _mesh = std::shared_ptr<Mesh>(mesh);
    } else {
        std::cout << "KOOOO\n";
        _mesh = nullptr;
    }
}

void Bomb::place()
{
    _isPlaced = true;
}

void Bomb::explode(IDisplay *d)
{
    _isPlaced = false;
    // if (_mesh)
    //     d->destroyCollision(_mesh);
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

Bomb::Mesh *Bomb::getMesh() const
{
    return _mesh.get();
}

std::string const Bomb::getRes() const
{
    return "../resources/models/Bomb/Bomb.obj";
}

std::string const Bomb::getTexture() const
{
    return "../resources/models/Bomb/Bomb.png";
}