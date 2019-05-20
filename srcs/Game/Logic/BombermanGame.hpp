#pragma once

#include <memory>

#include "Bot.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "IrrlichtDisplay.hpp"

class BombermanGame : public AGame {
public:
    using Map = std::vector<std::string>;

    BombermanGame(Players &, Bots &);
    ~BombermanGame() = default;
    ACharacter::Action              pressKeyAction(const Event &, const std::size_t &);
    std::vector<ACharacter::Action> moveBots(const Map &, IDisplay *) final;
    std::vector<ACharacter::Action> movePlayers(const Event &, const Map &,
            IDisplay *) final;
};