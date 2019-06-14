/*
** EPITECH PROJECT, 2019
** SceneException.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneException.hpp"

SceneException::SceneException(const char *what, const char *name) :
    _what(what),
    _name(name)
{}

const char *SceneException::what()
{
    return _what;
}