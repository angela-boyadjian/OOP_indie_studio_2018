/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Bomberman.hpp"

#include "Bot.hpp"
#include "Map.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "Player.hpp"
#include "Display.hpp"
#include "Menu.hpp"

#include <irrlicht.h>
#include <DisplayLoader.hpp>

int main()
{
    auto players = std::vector<std::unique_ptr<Player>>();
    players.push_back(std::make_unique<Player>(Player(ACharacter::Color::BLACK,
            std::make_tuple(std::size_t(0), std::size_t(0)))));
    auto bots = std::vector<std::unique_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(std::make_tuple(std::size_t(0),
            std::size_t(0)))));
    auto game = std::unique_ptr<AGame>(new Game(players, bots));
    core::Bomberman b;
    auto disp = std::unique_ptr<IDisplay>(new Display());
    b.setDisplayer(disp);
    b.loadGame("./../resources/maps/3", game);
    b.run();
    return 0;
}