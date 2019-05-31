/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include <irrlicht.h>
#include <IrrlichtDisplay/IrrlichtDisplayLoader.hpp>

#include "Bomberman.hpp"
#include "BombermanPlayers/Bot.hpp"
#include "Map.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "BombermanPlayers/Player.hpp"
#include "IrrlichtDisplay/IrrlichtDisplay.hpp"
#include "BombermanMenu/Menu.hpp"

int main()
{
    core::Bomberman b;

    b.lauch();
    return 0;
}