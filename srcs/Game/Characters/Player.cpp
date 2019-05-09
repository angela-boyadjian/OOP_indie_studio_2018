/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(MapPos const &pos, Display &display) : ACharacter(pos),
    _display(display)
{
}

Player::~Player()
{
}

void Player::loadPlayer()
{
    _display.addNewAnimation("../resources/models/Character/Bomberman.MD3",
        "../resources/models/Character/RedBombermanTextures.png",
        irr::core::vector3df(6, 6, 6));
}

void Player::displayPlayer()
{
    _display.draw();
}

void Player::move()
{

}