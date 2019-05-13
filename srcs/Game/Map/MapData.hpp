/*
** EPITECH PROJECT, 2019
** MapData.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "SpriteInfo.hpp"

struct MapData {
    std::vector<std::string> _mapData;
    std::unordered_map<char, SpriteInfo> _rules;
    unsigned int _time;
    unsigned int _nbEnnemie;

    //tempo
    int _scale;
};
