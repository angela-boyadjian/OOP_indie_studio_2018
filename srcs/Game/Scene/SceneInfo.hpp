/*
** EPITECH PROJECT, 2019
** SceneInfo.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include "IMap.hpp"
#include "ACharacter.hpp"

struct SceneInfo {
        SceneInfo(const std::string dest) : _dest(dest) {};

        std::string _dest;
        std::shared_ptr<IMap> _map;
        std::vector<std::shared_ptr<ACharacter>> _characters;
};



