#pragma once

#include <memory>

#include "Bot.hpp"
#include "IGame.hpp"
#include "Player.hpp"
#include "Events.hpp"
#include "Display.hpp"

class Game : public IGame {
public:
    using Map = std::vector<std::string>;
    using Bots = std::vector<std::unique_ptr<Bot>>;
    using Players = std::vector<std::unique_ptr<Player>>;

    Game() = default;
    Game(Players &, Bots &);
    ~Game() = default;
    void    moveBots(const Map &) final;
    void    movePlayers(const Events &, const Map &) final ;

private:
    Bots    _bots;
    Players _players;
};