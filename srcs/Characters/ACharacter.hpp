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

    typedef struct move_s {
        int     x;
        int     y;
        Action  action;
        ACharacter  *itself;
    }   move_t;

    // CONSTRUCTOR / DESTRUCTOR
    explicit ACharacter(const std::size_t &, const MapPos &,
            const Color & = Color::PINK);
    ~ACharacter() = default;

    // SETTERS
    void    setAction(const Action &);
    void    setPosZ(const float &);
    void    setPosY(const float &);
    void    setPosX(const float &);
    void    setPos2d(std::tuple<int, int> const &pos);
    void    setPos3d(std::tuple<float, float> const &pos);

    // GETTERS
    KeyMap              &getKeyMap();
    const MapPos        &getMapPos() const;
    const std::size_t   &getEntityNb() const;

    // DEPLACEMENT
    virtual move_t  move(std::vector<std::string> &, IDisplay *) = 0;

public:
    Color                       _color;
    std::vector<std::string>    _textures;
protected:
    MapPos                      _pos;
    std::tuple<float, float>    _3dPos;
    std::size_t                 _speed;
    KeyMap                      _keyMap;
    Action                      _action;
    std::size_t                 _entityNb;
    std::vector<std::string>    _transformedMap;
    std::tuple<int, int>_2dPos;
};
