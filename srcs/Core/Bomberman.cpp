/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#include <unistd.h>
#include <chrono>
#include <iostream>
#include <SFML/Audio.hpp>
#include <IrrlichtDisplayLoader.hpp>

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
        std::shared_ptr<IDisplayLoader> &dl)
{
    _display = std::move(d);
    _dispLoader = std::move(dl);
}

void core::Bomberman::setMusic()
{
    _mainMusic = std::make_unique<sf::Music>();
    _mainMusic->openFromFile("./../resources/sounds/BombermanSong.wav");
}

std::size_t core::Bomberman::getColiIndex(const int &x, const int &y)
{
    auto count {0};

    for (auto j {0}; j < y; ++j)
        for (std::size_t i {0}; i < _map->getMapData()._mapWall[j].size(); ++i)
            if (_map->getMapData()._mapWall[j][i] == '2')
                ++count;
    for (auto i {0}; i <= x; ++i)
        if (_map->getMapData()._mapWall[y][i] == '2')
            ++count;
    return count;
}

void    core::Bomberman::setExplosion(const int &x, const int &y)
{
    _display->getExplosionMap()[y][x]->setVisible(true);
    _explosionTime.emplace_back(std::chrono::system_clock::now());
    _explosionPos.emplace_back(std::make_tuple(x, y));
}

void    core::Bomberman::exploseEmpty(const int &x, const int &y)
{
    auto tmp_x = x;
    auto tmp_y = y;

    while (--tmp_x >= 0 and _map->getMapData()._mapWall[y][tmp_x] == '3') {
        _map->getMapData()._mapWall[y][tmp_x] = '0';
        setExplosion(tmp_x, y);
    }
    tmp_x = x;
    while (++tmp_x < _map->getMapData()._mapWall[y].size() and _map->getMapData()._mapWall[y][tmp_x] == '3') {
        _map->getMapData()._mapWall[y][tmp_x] = '0';
        setExplosion(tmp_x, y);
    }
    while (--tmp_y >= 0 and _map->getMapData()._mapWall[tmp_y][x] == '3') {
        _map->getMapData()._mapWall[tmp_y][x] = '0';
        setExplosion(x, tmp_y);
    }
    tmp_y = y;
    while (++tmp_y < _map->getMapData()._mapWall.size() and _map->getMapData()._mapWall[tmp_y][x] == '3') {
        _map->getMapData()._mapWall[tmp_y][x] = '0';
        setExplosion(x, tmp_y);
    }
}

void    core::Bomberman::exploseBlock(const int &x, const int &y)
{
    if (x > 0 and _map->getMapData()._mapWall[y][x - 1] == '2') {
        _display->getColiMap().at(getColiIndex(x - 1, y))->setVisible(false);
        _map->getMapData()._mapWall[y][x - 1] = '0';
        setExplosion(x - 1, y);
    }
    if (x + 1 < _map->getMapData()._mapWall[y].size() and _map->getMapData()._mapWall[y][x + 1] == '2') {
        _display->getColiMap().at(getColiIndex(x + 1, y))->setVisible(false);
        _map->getMapData()._mapWall[y][x + 1] = '0';
        setExplosion(x + 1, y);
    }
    if (y > 0 and _map->getMapData()._mapWall[y - 1][x] == '2') {
        _display->getColiMap().at(getColiIndex(x - 1, y - 1))->setVisible(false);
        _map->getMapData()._mapWall[y - 1][x] = '0';
        setExplosion(x, y - 1);
    }
    if (y + 1 < _map->getMapData()._mapWall.size() and _map->getMapData()._mapWall[y + 1][x] == '2') {
        _display->getColiMap().at(getColiIndex(x, y + 1))->setVisible(false);
        _map->getMapData()._mapWall[y + 1][x] = '0';
        setExplosion(x, y + 1);
    }
    setExplosion(x, y);
    _map->getMapData()._mapWall[y][x] = '0';
    exploseEmpty(x, y);
}

void    core::Bomberman::stopExplosion()
{
    for (std::size_t i {0}; i < _explosionPos.size(); ++i) {
        std::chrono::duration<double>   elapsedTime = std::chrono::system_clock::now() - _explosionTime[i];
        if (elapsedTime.count() >= 1) {
            _display->getExplosionMap()[std::get<1>(_explosionPos[i])][std::get<0>(_explosionPos[i])]->setVisible(false);
            _explosionTime.erase(_explosionTime.begin() + i);
            _explosionPos.erase(_explosionPos.begin() + i);
            return stopExplosion();
        }
    }
}

void    core::Bomberman::explosion(const int &x, const int &y)
{
    exploseBlock(x, y);
    exploseEmpty(x, y);
}

void    core::Bomberman::exploseBomb()
{
    for (std::size_t i {0}; i < bombs_pos.size(); ++i) {
        std::chrono::duration<double>   elapsedTime = std::chrono::system_clock::now() - bombs_time[i];
        if (elapsedTime.count() >= 1) {
            explosion(bombs_pos[i].x, bombs_pos[i].y);
            _display->visiBomb(bombs_pos[i].x, bombs_pos[i].y, false);
            bombs_player[i]->increaseBombNumber();
            bombs_player.erase(bombs_player.begin() + i);
            bombs_time.erase(bombs_time.begin() + i);
            bombs_pos.erase(bombs_pos.begin() + i);
            return exploseBomb();
        }
    }
}

void    core::Bomberman::putBomb(const std::vector<ACharacter::move_t> &actions)
{
    for (auto a : actions) {
        if (a.action == ACharacter::Action::BOMB) {
            _display->visiBomb(a.x, a.y, true);
            bombs_pos.emplace_back(a);
            bombs_time.emplace_back(std::chrono::system_clock::now());
            bombs_player.emplace_back(reinterpret_cast<ABombermanPlayer *>(a.itself));
        }
    }
}

void core::Bomberman::run()
{
    // TEMPO - REPLACE IT BY GENERIC METHOD
    _game->getPlayers()[0]->setPosZ(std::get<2>(_game->getPlayers()[0]->getMapPos()) + 30);
    _display->changeModelPos(_game->getPlayers()[0]->getEntityNb(), std::make_tuple(
            std::get<0>(_game->getPlayers()[0]->getMapPos()),
            std::get<1>(_game->getPlayers()[0]->getMapPos()),
            std::get<2>(_game->getPlayers()[0]->getMapPos())));

    // TEMPO - REPLACE IT BY GENERIC METHOD
    _game->getBots()[0]->setPosZ(std::get<2>(_game->getPlayers()[0]->getMapPos()) - 100);
    _display->changeModelPos(_game->getBots()[0]->getEntityNb(), std::make_tuple(
            std::get<0>(_game->getBots()[0]->getMapPos()),
            std::get<1>(_game->getBots()[0]->getMapPos()),
            std::get<2>(_game->getBots()[0]->getMapPos())));
    _map->getMapData()._mapWall[10][0] = '0';


    while (_display->isRunning()) {
        if (_mainMusic->getStatus() != sf::Sound::Playing)
            _mainMusic->play();
        exploseBomb();
        auto actions = action();
        putBomb(actions);
        stopExplosion();
        _display->draw();
    }
}

std::vector<ACharacter::move_t> core::Bomberman::botsAction()
{
    auto botsMove = _game->moveBots(_map->getMapData()._mapWall, _display.get());
    for (std::size_t i {0}; i < _game->getBots().size(); ++i) {
        changeFrameAndPos(_game->getBots()[i].get(), botsMove[i].action, _lastActions[_game->getBots()[i]->getEntityNb()]);
        changeAnimation(_game->getBots()[i]->getEntityNb(), botsMove[i].action, _lastActions[_game->getBots()[i]->getEntityNb()]);
        _lastActions[_game->getBots()[i]->getEntityNb()] = botsMove[i].action;
    }
    return botsMove;
}

std::vector<ACharacter::move_t> core::Bomberman::playersAction()
{
    auto playersMove = _game->movePlayers(_event, _map->getMapData()._mapWall, _display.get());
    for (std::size_t i {0}; i < _game->getPlayers().size(); ++i) {
        changeFrameAndPos(_game->getPlayers()[i].get(), playersMove[i].action, _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        changeAnimation(_game->getPlayers()[i]->getEntityNb(), playersMove[i].action, _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        _lastActions[_game->getPlayers()[i]->getEntityNb()] = playersMove[i].action;
    }
    return playersMove;
}

std::vector<ACharacter::move_t> core::Bomberman::action()
{
    auto p = playersAction();
    auto b = botsAction();
    p.insert(p.end(), b.begin(), b.end());
    return p;
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

    _map = std::unique_ptr<IMap>(new Map);
    _map->load(mapPath);
// _map->generate3dMap(-1, 80, -1); GENERATION PROCEDURALE
    _game = std::move(game);
    _dispLoader->loadGame(_game);
    _dispLoader->loadMap(_map->getMapData());
    _dispLoader->loadMenu(menu);

    // NOTE TEMPO
    _event = std::make_unique<Events>(Events(_display->_device, _display));
    _display->_device->setEventReceiver(_event.get());
}

void    core::Bomberman::lauch()
{
    auto disp = std::shared_ptr<IDisplay>(new IrrlichtDisplay());
    _event = std::make_unique<Events>(Events(disp->_device, _display));
    disp->setDisplay(_event.get());
    auto dispLoader = std::shared_ptr<IDisplayLoader>(new IrrlichtDisplayLoader(disp));
    setDisplayer(disp, dispLoader);
    setMusic();
    initGame(_event.get());
    run();
}

void    core::Bomberman::initGame(Events *event)
{
   auto players = std::vector<std::unique_ptr<Player>>();
    players.push_back(std::make_unique<Player>(Player(0, ACharacter::Color::BLACK,
                                                      std::make_tuple(std::size_t(0), std::size_t(0), std::size_t(0)))));
    auto bots = std::vector<std::unique_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(1, std::make_tuple(std::size_t(0),
                                                             std::size_t(0), std::size_t(0)))));
    auto game = std::unique_ptr<AGame>(new BombermanGame(players, bots));
    loadGame("./../resources/maps/3", game);
}