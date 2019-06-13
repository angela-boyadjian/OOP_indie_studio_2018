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

namespace core {
    class Bomberman;
}

class core::Bomberman {
public:
    using Event = std::unique_ptr<Events>;
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

    // BombermanGame loop
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

//    std::vector<IDisplay::Scenes> _sceneManager;
};