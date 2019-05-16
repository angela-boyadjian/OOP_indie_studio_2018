/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#include "ACharacter.hpp"

// NOTE CONSTRUCTOR / DESTRUCTOR
ACharacter::ACharacter(const MapPos &pos, const Color &color) :
    _textures({"../resources/models/Character/BlackBombermanTextures.png",
    "../resources/models/Character/PinkBombermanTextures.png", 
    "../resources/models/Character/RedBombermanTextures.png",
    "../resources/models/Character/WhiteBombermanTextures.png"}),
    _pos(pos), _color(color), _speed(1),
    _fireRange(1), _bombNumber(1), _maxBombNumber(1)
{
}

// SETTERS
void    ACharacter::setAction(const ACharacter::Action &action)
{
    _action = action;
}

// GETTERS
ACharacter::KeyMap          &ACharacter::getKeyMap() { return _keyMap; }
const ACharacter::MapPos    &ACharacter::getMapPos() const { return _pos; }
const std::size_t           &ACharacter::getFireRange() const { return _fireRange; }
const ACharacter::Action    &ACharacter::getDirection() const { return _action; }

// INCREASER
void    ACharacter::increaseSpeed() { _speed += 1; }
void    ACharacter::increaseFireRange() { _fireRange += 1; }
void    ACharacter::increaseBombNumber() { _bombNumber += 1; }

// DECREASER
void    ACharacter::decreaseBombNumber() { _bombNumber -= 1; }