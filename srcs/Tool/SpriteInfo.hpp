/*
** EPITECH PROJECT, 2019
** SpriteData.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <irrlicht.h>
#include <iostream>

struct SpriteInfo {
    enum class COLID {

    };

    SpriteInfo(const std::string &referTo, const std::string &messPath,
               const std::string &textPath,
               const irr::core::vector3df &size) : _referTo(referTo),
                                                   _messPath(messPath),
                                                   _texPath(textPath),
                                                   _size(size)
    {}
    std::string _referTo;
    std::string _messPath;
    std::string _texPath;
    irr::core::vector3df _size;
};
