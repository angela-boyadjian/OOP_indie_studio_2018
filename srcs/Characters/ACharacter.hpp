/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#pragma once

#include <map>
#include <tuple>
#include <vector>
#include <string>

#include "Events.hpp"
#include "IDisplay.hpp"

class ACharacter {
public:
    using MapPos = std::tuple<float, float, float>;
    using KeyMap = std::map<std::string, irr::EKEY_CODE>;

    // DIRECTION OF THE CHARACTER
    enum class Action {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        BOMB,
        WAIT
    };

    enum class Color {
        BLACK,
        PINK,
        RED,
        WHITE
    };

    // CONSTRUCTOR / DESTRUCTOR
    explicit ACharacter(const std::size_t &, const MapPos &,
            const Color & = Color::PINK);
    ~ACharacter() = default;

    // SETTERS
    void    setAction(const Action &);
    void    setPosZ(const std::size_t &);

    // GETTERS
    KeyMap              &getKeyMap();
    const MapPos        &getMapPos() const;
    const std::size_t   &getEntityNb() const;

    // DEPLACEMENT
    virtual void    move(const std::vector<std::string> &, IDisplay *) = 0;

public:
    Color                       _color;
    std::vector<std::string>    _textures;
protected:
    MapPos                      _pos;
    std::size_t                 _speed;
    KeyMap                      _keyMap;
    Action                      _action;
    std::size_t                 _entityNb;
};
