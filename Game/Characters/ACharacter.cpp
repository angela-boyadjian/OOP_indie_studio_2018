#include "ACharacter.hpp"

// CONSTRUCTOR / DESTRUCTOR
ACharacter::ACharacter(const MapPos &pos) :
    _pos(pos), _speed(1), _fireRange(1), _bombNumber(1), _maxBombNumber(1) {}

// GETTERS
const MapPos                &ACharacter::getMapPos() const { return _pos; }
const std::size_t           &ACharacter::getFireRange() const { return _fireRange; }
const ACharacter::Direction &ACharacter::getDirection() const { return _direction; }

// INCREASER
void    ACharacter::increaseSpeed() { _speed += 1; }
void    ACharacter::increaseFireRange() { _fireRange += 1; }
void    ACharacter::increaseBombNumber() { _bombNumber += 1; }
