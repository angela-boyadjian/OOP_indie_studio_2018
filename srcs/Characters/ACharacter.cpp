/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#include "ACharacter.hpp"

// NOTE CONSTRUCTOR / DESTRUCTOR
ACharacter::ACharacter(const std::size_t &enb, const MapPos &pos,
        const Color &color) :
    _textures({"../resources/models/Character/BlackBombermanTextures.png",
    "../resources/models/Character/PinkBombermanTextures.png", 
    "../resources/models/Character/RedBombermanTextures.png",
    "../resources/models/Character/WhiteBombermanTextures.png"}),
    _pos(pos), _color(color), _speed(1), _entityNb(enb)
{
    _keyMap["UP"] = irr::EKEY_CODE::KEY_KEY_Z;
    _keyMap["DOWN"] = irr::EKEY_CODE::KEY_KEY_S;
    _keyMap["LEFT"] = irr::EKEY_CODE::KEY_KEY_Q;
    _keyMap["RIGHT"] = irr::EKEY_CODE::KEY_KEY_D;
    _keyMap["BOMB"] = irr::EKEY_CODE::KEY_KEY_B;
}

// SETTERS
void    ACharacter::setAction(const ACharacter::Action &action) { _action = action; }
void    ACharacter::setPosZ(const float &z) { std::get<2>(_pos) = z; }
void    ACharacter::setPosY(const float &y) { std::get<1>(_pos) = y; }
void    ACharacter::setPosX(const float &x) { std::get<0>(_pos) = x; }
void    ACharacter::setPos2d(std::tuple<int, int> const &pos) { _2dPos = pos; }

// GETTERS
ACharacter::KeyMap          &ACharacter::getKeyMap() { return _keyMap; }
const ACharacter::MapPos    &ACharacter::getMapPos() const { return _pos; }
const std::size_t           &ACharacter::getEntityNb() const { return _entityNb; }