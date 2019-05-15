#pragma once

#include <memory>

#include "Bot.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "Display.hpp"

class Game : public AGame {
public:
    using Map = std::vector<std::string>;

    Game() = default;
    Game(Players &, Bots &);
    ~Game() = default;
    void    moveBots(const Map &) final;
    void    movePlayers(const Events &, const Map &) final;
};