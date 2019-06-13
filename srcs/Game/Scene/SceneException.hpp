/*
** EPITECH PROJECT, 2019
** SceneException.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include <iostream>

class SceneException : public std::exception {
    public:
        SceneException(const char *, const char *name);
        ~SceneException() = default;

        const char *what();
    private:
        const char *_what;
        const char *_name;
};



