#pragma once

#include <vector>

#include "Events.hpp"

class IGame {
    using Map = std::vector<std::string>;

    virtual void    moveBots(const Map &) = 0;
    virtual void    movePlayers(const Events &, const Map &) = 0;
};