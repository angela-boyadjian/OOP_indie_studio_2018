/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/

#pragma once

#include <string>

class Map {
public:
    Map(std::string const &);
    ~Map();

    void displayMap();
private:
    std::string _filename;
};