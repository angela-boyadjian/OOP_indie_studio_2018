/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ABombermanPlayer
*/

#include "ABombermanPlayer.hpp"

ABombermanPlayer::ABombermanPlayer(const std::size_t &enb, const MapPos &pos,
                       const Color &color) : ACharacter(enb, pos, color),
        _fireRange(1), _bombNumber(1), _maxBombNumber(1)
{
    _textures = std::vector<std::string>({"../resources/models/Character/BlackBombermanTextures.png",
               "../resources/models/Character/PinkBombermanTextures.png",
               "../resources/models/Character/RedBombermanTextures.png",
               "../resources/models/Character/WhiteBombermanTextures.png"});
}

// SETTERS
const bool                  &ABombermanPlayer::canShoot() const { return _canShoot; };
const std::size_t           &ABombermanPlayer::getFireRange() const { return _fireRange; }
const ACharacter::Action    &ABombermanPlayer::getDirection() const { return _action; }

// INCREASER
void    ABombermanPlayer::increaseSpeed() { _speed += 1; }
void    ABombermanPlayer::increaseFireRange() { _fireRange += 1; }
void    ABombermanPlayer::increaseBombNumber() { _bombNumber += 1; }

// DECREASER
void    ABombermanPlayer::decreaseBombNumber() { _bombNumber -= 1; }