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
#include "Menu.hpp"

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
/*    _game->getPlayers()[0]->setPosZ(std::get<2>(_game->getPlayers()[0]->getMapPos()) + 30);
    _display->changeModelPos(_game->getPlayers()[0]->getEntityNb(), std::make_tuple(
            std::get<0>(_game->getPlayers()[0]->getMapPos()),
                    std::get<1>(_game->getPlayers()[0]->getMapPos()),
                            std::get<2>(_game->getPlayers()[0]->getMapPos())));*/
    while (_display->isRunning()) {
//        action();
        _display->draw();
    }
}

void    core::Bomberman::botsAction()
{
    auto botsMove = _game->moveBots(_map->getMapData()._mapWall, _display.get());
    for (std::size_t i {0}; i < _game->getBots().size(); ++i) {
        changeFrameAndPos(_game->getBots()[i].get(), botsMove[i], _lastActions[_game->getBots()[i]->getEntityNb()]);
        changeAnimation(_game->getBots()[i]->getEntityNb(), botsMove[i], _lastActions[_game->getBots()[i]->getEntityNb()]);
        _lastActions[_game->getBots()[i]->getEntityNb()] = botsMove[i];
    }
}

void    core::Bomberman::playersAction()
{
    auto playersMove = _game->movePlayers(_event, _map->getMapData()._mapWall, _display.get());
    for (std::size_t i {0}; i < _game->getPlayers().size(); ++i) {
        changeFrameAndPos(_game->getPlayers()[i].get(), playersMove[i], _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        changeAnimation(_game->getPlayers()[i]->getEntityNb(), playersMove[i], _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        _lastActions[_game->getPlayers()[i]->getEntityNb()] = playersMove[i];
    }
}

void    core::Bomberman::action()
{
    playersAction();
    botsAction();
}

void    core::Bomberman::changeAnimation(const std::size_t &i, const ACharacter::Action &curr,
        const ACharacter::Action &last)
{
    switch (curr) {
        case ACharacter::Action::LEFT:
            _display->changeModelRot(i, std::make_tuple(0, 90, 0));
            break;
        case ACharacter::Action::RIGHT:
            _display->changeModelRot(i, std::make_tuple(0, 270, 0));
            break;
        case ACharacter::Action::UP:
            _display->changeModelRot(i, std::make_tuple(0, 180, 0));
            break;
        case ACharacter::Action::DOWN:
            _display->changeModelRot(i, std::make_tuple(0, 0, 0));
            break;
        case ACharacter::Action::WAIT:
            if (last != ACharacter::Action::WAIT)
                _display->changeModelFrame(i, 27, 76);
            break;
        default:
            break;
    }
}

void    core::Bomberman::changeFrameAndPos(const ACharacter *cha, const ACharacter::Action &curr,
                                           const ACharacter::Action &last)
{
    if (curr != ACharacter::Action::WAIT) {
        if (last == ACharacter::Action::WAIT)
            _display->changeModelFrame(cha->getEntityNb(), 0, 27);
        _display->changeModelPos(cha->getEntityNb(), std::make_tuple(std::get<0>(cha->getMapPos()),
            0, std::get<2>(cha->getMapPos())));
    }
}

void core::Bomberman::loadGame(const std::string &mapPath, std::unique_ptr<AGame> &game)
{
    auto menu = std::unique_ptr<Menu>(new Menu());

//    _map = std::unique_ptr<IMap>(new Map(mapPath));
//    _map->load();
//    _game = std::move(game);
 //   _dispLoader->loadGame(_game);
 //   _dispLoader->loadMap(_map->getMapData());
    _dispLoader->loadMenu(menu);
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
                                                      std::make_tuple(std::size_t(0), std::size_t(0), std::size_t(0)))));
    auto bots = std::vector<std::unique_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(1, std::make_tuple(std::size_t(0),
                                                             std::size_t(0), std::size_t(0)))));
    auto game = std::unique_ptr<AGame>(new Game(players, bots));
    loadGame("./../resources/maps/3", game);
}