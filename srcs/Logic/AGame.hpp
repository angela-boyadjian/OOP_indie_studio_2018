#pragma once

#include <vector>
#include <chrono>

#include "BombermanPlayers/Bot.hpp"
#include "Events.hpp"
#include "BombermanPlayers/Player.hpp"

class AGame {
public:
    using Map = std::vector<std::string>;
    using Bots = std::vector<std::shared_ptr<Bot>>;
    using Players = std::vector<std::shared_ptr<Player>>;
    using Event = std::shared_ptr<Events>;
    using Timer = std::chrono::time_point<std::chrono::system_clock>;

    // CONSTRUCOR / DESTRUCTOR
    AGame(Players &p, Bots &b) :
            _bots(std::move(b)), _score(0), _players(std::move(p)) {
        _secondsElapsed = std::chrono::system_clock::now();
    }
    ~AGame() = default;

    // GETTERS
    std::size_t getScore() const { return _score; }
    long        getElapsedSedonds() const {
        return std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - _secondsElapsed).count();
    }
    Bots      &getBots() { return _bots; }
    Players   &getPlayers() { return _players; }

    // DEPLACEMENTS (PURE METHODS)
    virtual std::vector<ACharacter::move_t> moveBots(Map &, IDisplay *) = 0;
    virtual std::vector<ACharacter::move_t> movePlayers(const Event &, Map &,
            IDisplay *) = 0;

protected:
    Bots        _bots;
    std::size_t _score;
    Players     _players;
    Timer       _secondsElapsed;
};