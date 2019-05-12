/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/
#include "ACharacter.hpp"

// NOTE CONSTRUCTOR / DESTRUCTOR
ACharacter::ACharacter(const MapPos &pos) :
    _textures({"../resources/models/Character/BlackBombermanTextures.png",
    "../resources/models/Character/PinkBombermanTextures.png", 
    "../resources/models/Character/RedBombermanTextures.png",
    "../resources/models/Character/WhiteBombermanTextures.png"}),
    _pos(pos), _speed(1),
    _fireRange(1), _bombNumber(1), _maxBombNumber(1)
{
    
}

// NOTE GETTERS
const ACharacter::MapPos    &ACharacter::getMapPos() const { return _pos; }
const std::size_t           &ACharacter::getFireRange() const { return _fireRange; }
const ACharacter::Direction &ACharacter::getDirection() const { return _direction; }

// NOTE INCREASER
void    ACharacter::increaseSpeed() { _speed += 1; }
void    ACharacter::increaseFireRange() { _fireRange += 1; }
void    ACharacter::increaseBombNumber() { _bombNumber += 1; }