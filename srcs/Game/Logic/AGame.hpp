#pragma once

#include <vector>
#include <chrono>

#include "Events.hpp"
#include "Player.hpp"

class AGame {
public:
    using Map = std::vector<std::string>;
    using Bots = std::vector<std::unique_ptr<Bot>>;
    using Players = std::vector<std::unique_ptr<Player>>;
    using Event = std::unique_ptr<Events<irr::IEventReceiver>>;
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

    // DEPLACEMENTS (PURE METHODS)
    virtual void    moveBots(const Map &) = 0;
    virtual void    movePlayers(const Event &, const Map &) = 0;

protected:
    Bots        _bots;
    std::size_t _score;
    Players     _players;
    Timer       _secondsElapsed;
};