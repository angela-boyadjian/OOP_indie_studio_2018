/*
** EPITECH PROJECT, 2019
** SceneManagerException.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include <iostream>

class SceneManagerException : public std::exception {
    public:
        SceneManagerException(const char *, const char *);
        ~SceneManagerException() = default;

        const char *what();
    private:
        const char *_what;
        const char *_name;
};



