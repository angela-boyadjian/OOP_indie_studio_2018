#pragma once

#include <memory>

#include "Bot.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "Display.hpp"

class Game : public AGame {
public:
    using Map = std::vector<std::string>;

    Game(Players &, Bots &);
    ~Game() = default;
    std::vector<ACharacter::Action> moveBots(const Map &) final;
    std::vector<ACharacter::Action> movePlayers(const Event &, const Map &) final;
};