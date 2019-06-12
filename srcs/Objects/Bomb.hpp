/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#pragma once

#include <string>

#include "IDisplay.hpp"

class Bomb {
public:
    using Mesh = irr::scene::IAnimatedMeshSceneNode;

    Bomb();
    // Bomb(Bomb const &) = delete;
    // Bomb &operator=(Bomb const &) = delete;
    ~Bomb();

    // NOTE Action
    void explode(IDisplay *);
    void place();
    bool isPlaced() const;
    bool isOn() const;
    void addMesh(Mesh *);

    // NOTE Setter
    void setOn(bool);

    // NOTE Getters
    Mesh *getMesh() const;
    std::string const getRes() const;
    std::string const getTexture() const;
private:
    bool        _isPlaced;
    bool        _on;
    std::shared_ptr<Mesh>     _mesh;
};