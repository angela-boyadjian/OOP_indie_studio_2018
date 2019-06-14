/*
** EPITECH PROJECT, 2019
** SceneManagerException.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneManagerException.hpp"

SceneManagerException::SceneManagerException(const char *what, const char *name) :
    _what(what),
    _name(name)
{}

const char *SceneManagerException::what()
{
    return _what;
}