/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#pragma once

#include <memory>
#include <SFML/Audio.hpp>

#include "Map.hpp"
#include "Bomberman/BombermanGame.hpp"
#include "AGame.hpp"
#include "BombermanPlayers/Player.hpp"
#include "IDisplayLoader.hpp"
#include "ISceneManager.hpp"
#include "SceneManager.hpp"

namespace core {
    class Bomberman;
}

class core::Bomberman {
public:
    using Event = std::shared_ptr<Events>;
    using botVec = std::vector<std::unique_ptr<Bot>>;
    using playerVec = std::vector<std::unique_ptr<Player>>;

    Bomberman();
    ~Bomberman();

    // SETTERS
    void    setGame(std::unique_ptr<AGame> &);
    void    setDisplayer(std::shared_ptr<IDisplay> &, std::shared_ptr<IDisplayLoader> &);
    void    setMusic();

    // load resources
    void    loadGame(const std::string &, std::unique_ptr<AGame> &);

    // scene manager
    void initScene();

    // TEMPO DANS LE MERGE
    void Trun();

    // BombermanGame loop
    std::size_t getColiIndex(const int &, const int &);
    void    setExplosion(const int &, const int &);
    void    stopExplosion();
    void    removeBlock(const int &, const int &, bool);
    void    exploseEmpty(const int &, const int &);
    void    exploseBlock(const int &, const int &);
    void    explosion(const int &, const int &);
    void    exploseBomb();
    void    putBomb(const std::vector<ACharacter::move_t> &);
    void    run();
    std::vector<ACharacter::move_t> action();
    std::vector<ACharacter::move_t> botsAction();
    std::vector<ACharacter::move_t> playersAction();
    void    changeAnimation(const std::size_t &, const ACharacter::Action &, const ACharacter::Action &);
    void    changeFrameAndPos(const ACharacter *, const ACharacter::Action &, const ACharacter::Action &);

    // LAUNCH CORE
    void    lauch();
    void    initGame(Events *event);

private:
    std::unique_ptr<IMap>           _map;
    std::unique_ptr<AGame>          _game;
    Event                           _event;
    std::shared_ptr<IDisplay>       _display;
    std::shared_ptr<IDisplayLoader> _dispLoader;
    std::map<std::size_t, ACharacter::Action>   _lastActions;
    std::unique_ptr<sf::Music>      _mainMusic;
    SceneManager _manager;
    // BOMBS
    std::vector<ACharacter::move_t>     bombs_pos;
    std::vector<ABombermanPlayer *>     bombs_player;
    std::vector<std::chrono::time_point<std::chrono::system_clock>> bombs_time;
    // EXPLOSION
    std::vector<std::tuple<int, int>>   _explosionPos;
    std::vector<std::chrono::time_point<std::chrono::system_clock>> _explosionTime;
    std::vector<std::size_t> _rm;
//    std::vector<IDisplay::Scenes> _sceneManager;
};