/*
** EPITECH PROJECT, 2019
** Reader.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "SpriteInfo.hpp"

class Reader {
    public:
        Reader() = default;
        ~Reader() = default;

        std::vector<std::string> vectorRead(const std::string &);
        std::string stringRead(const std::string &);
        std::vector<SpriteInfo> readSpriteInfo(const std::string &);

};