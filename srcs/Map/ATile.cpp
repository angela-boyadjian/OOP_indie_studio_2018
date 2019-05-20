/*
** EPITECH PROJECT, 2019
** ATile.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "ATile.hpp"



// NOTE GETTER SETTER

unsigned int ATile::getIndex() const
{
    return _index;
}

void ATile::setIndex(unsigned int index)
{
    _index = index;
}

ATile::TYPE ATile::getType() const
{
    return _type;
}

void ATile::setType(ATile::TYPE type)
{
    _type = type;
}
