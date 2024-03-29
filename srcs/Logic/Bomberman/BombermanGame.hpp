#pragma once

#include <memory>

#include "BombermanPlayers/Bot.hpp"
#include "AGame.hpp"
#include "Events.hpp"
#include "IrrlichtDisplay/IrrlichtDisplay.hpp"

class BombermanGame : public AGame {
public:
    using Map = std::vector<std::string>;

    BombermanGame(Players &, Bots &);
    ~BombermanGame() = default;
    ACharacter::Action              pressKeyAction(const Event &, const std::size_t &);
    std::vector<ACharacter::move_t> moveBots(Map &, IDisplay *) final;
    std::vector<ACharacter::move_t> movePlayers(const Event &, Map &,
            IDisplay *) final;
};