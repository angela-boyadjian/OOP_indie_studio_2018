/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#include <iostream>
#include <DisplayLoader.hpp>

#include "Bomberman.hpp"
#include "ACharacter.hpp"

core::Bomberman::Bomberman()
{
}

core::Bomberman::~Bomberman()
{
}

// SETTERS
void core::Bomberman::setGame(std::unique_ptr<AGame> &g)
{
    _game = std::move(g);
}

void core::Bomberman::setDisplayer(std::shared_ptr<IDisplay> &d,
        std::unique_ptr<IDisplayLoader> &dl)
{
    _display = std::move(d);
    _dispLoader = std::move(dl);
}

void core::Bomberman::run()
{
    auto tmp = ACharacter::Action::WAIT;
    while (_display->isRunning()) {
        auto a = _game->movePlayers(_event, _map->getMapData()._mapWall);
        changeFrameAndPos(_game->getPlayers()[0]->getEntityNb(), a, tmp);
        auto b = _game->moveBots(_map->getMapData()._mapWall);
        if (b != ACharacter::Action::WAIT)
            _display->changeModelPos(_game->getBots()[0]->getEntityNb(), irr::core::vector3df(std::get<0>(_game->getBots()[0]->getMapPos()),
                                                          std::get<1>(_game->getBots()[0]->getMapPos()), 0));
        changeAnimation(_game->getPlayers()[0]->getEntityNb(), a, tmp);
        tmp = a;
        _display->draw();
    }
}

void    core::Bomberman::changeAnimation(const std::size_t &i, const ACharacter::Action &curr,
        const ACharacter::Action &last)
{
    switch (curr) {
        case ACharacter::Action::LEFT:
            _display->changeModelRot(i, irr::core::vector3df(0, 90, 0));
            break;
        case ACharacter::Action::RIGHT:
            _display->changeModelRot(i, irr::core::vector3df(0, 270, 0));
            break;
        case ACharacter::Action::UP:
            _display->changeModelRot(i, irr::core::vector3df(0, 180, 0));
            break;
        case ACharacter::Action::DOWN:
            _display->changeModelRot(i, irr::core::vector3df(0, 0, 0));
            break;
        case ACharacter::Action::WAIT:
            if (last != ACharacter::Action::WAIT)
                _display->changeModelFrame(i, 27, 76);
            break;
        default:
            break;
    }
}

void    core::Bomberman::changeFrameAndPos(const std::size_t &i, const ACharacter::Action &curr,
                                           const ACharacter::Action &last)
{
    if (curr != ACharacter::Action::WAIT) {
        if (last == ACharacter::Action::WAIT)
            _display->changeModelFrame(_game->getPlayers()[0]->getEntityNb(), 0, 27);
        _display->changeModelPos(_game->getPlayers()[0]->getEntityNb(), irr::core::vector3df(std::get<0>(_game->getPlayers()[0]->getMapPos()),
                                                                                             std::get<1>(_game->getPlayers()[0]->getMapPos()), 0));
    }
}

void core::Bomberman::loadGame(const std::string &mapPath, std::unique_ptr<AGame> &game)
{
    _map = std::unique_ptr<IMap>(new Map(mapPath));
    _map->load();
    _game = std::move(game);
    _display->setCameraScene();
    _dispLoader->loadGame(_game);
    _dispLoader->loadMap(_map->getMapData());
}

void    core::Bomberman::lauch()
{
    auto disp = std::shared_ptr<IDisplay>(new Display());
    std::cout << "1" << std::endl;
    _event = std::make_unique<Events>(Events(disp->_device));
    disp->setDisplay(_event.get());
    auto dispLoader = std::unique_ptr<IDisplayLoader>(new DisplayLoader(disp));
    setDisplayer(disp, dispLoader);
    initGame();
    run();
}

void    core::Bomberman::initGame()
{
    auto players = std::vector<std::unique_ptr<Player>>();
    players.push_back(std::make_unique<Player>(Player(0, ACharacter::Color::BLACK,
                                                      std::make_tuple(std::size_t(0), std::size_t(0)))));
    auto bots = std::vector<std::unique_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(1, std::make_tuple(std::size_t(0),
                                                             std::size_t(0)))));
    auto game = std::unique_ptr<AGame>(new Game(players, bots));
    loadGame("./../resources/maps/3", game);
}